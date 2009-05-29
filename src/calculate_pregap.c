/**
 * Copyright (C) 2009 
 *	- Salvatore Santagati <salvatore.santagati@gmail.com>
 * 	- Abdur Rab <c.abdur@yahoo.com>
 *
 * All rights reserved.
 *
 * This program is free software; under the terms of the 
 * GNU General Public License as published by the Free Software Foundation; 
 * either version 2 of the License, or (at your option) any later version.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are
 * met:
 *
 * @ Redistributions of source code must retain the above copyright
 *   notice, this list of conditions and the following disclaimer. 
 *
 * @ Redistributions in binary form must reproduce the above copyright
 *   notice, this list of conditions and the following disclaimer in
 *   the documentation and/or other materials provided with the
 *   distribution. 
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the
 * Free Software Foundation, Inc.,
 * 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
 */

#ifndef CALCULATE_PREGAP_H
#include "calculate_pregap.h"
#endif

int is_udf_image  ( unsigned char* header )
{
        int number = 7;
        int size = 5;
        /* UDF HEADER */
        unsigned const char udf_header [ 7 ] [ 5 ] = {
                { 0x42, 0x45, 0x41, 0x30, 0x31 }, /* BEA01 */
                { 0x42, 0x4F, 0x4F, 0x54, 0x32 }, /* BOOT2 */
                { 0x43, 0x44, 0x30, 0x30, 0x31 }, /* CD001 */
                { 0x43, 0x44, 0x57, 0x30, 0x32 }, /* CDW02 */
                { 0x4E, 0x5D, 0x5C, 0x30, 0x32 }, /* NSR02 */
                { 0x4E, 0x5D, 0x5C, 0x30, 0x33 }, /* NSR03 */
                { 0x54, 0x45, 0x41, 0x30, 0x31 }  /* TEA01 */
        };

        int n_count = 0;
        int n_return_value = ERROR;
        for ( n_count = 0; n_count < number; n_count++ ) {
                if ( ( !memcmp ( header, udf_header [ n_count ], size ) ) ) {
                        n_return_value = AOK;
                        break;
                }
        }

        return ( n_return_value );
}


/* --- @calculate_pregap_length@ --- *
 *  
 * Arguments: 	@off_t cd_id_start@ = bytes when is detect primary volume of CD/DVD
 *		@int block@ = block size of image 
 *		@int header@ = header of block  	
 * 
 * Returns : 	Pregap of image.
 * 
 * Use:		Return pregap of image.	 
 */
off_t calculate_pregap_length ( off_t  cd_id_start, image_struct* img_struct, int header )
{
	return ( ( cd_id_start - ( img_struct -> block * 16 ) ) - header - 1); 
}

/* --- @calculate_block_size@ --- *
 *
 * Arguments:	@off_t cd_id_start@ = bytes when is detect primary volume of CD/DVD 
 *		@off_t cd_id_end@	= bytes when is present next volume of CD/DVD
 * 
 * Returns :	block size.
 * 
 * Use:		Return block size image.
 */
int calculate_block_size (  off_t cd_id_start, off_t cd_id_end, image_struct* img_struct )
{

	int block_sizes [ ] = { 2048, 2336, 2352, 2448 };
	size_t block  = cd_id_end - cd_id_start;

	img_struct -> block  = ( ( block % block_sizes [ 0 ] ) == 0 ) ? block_sizes [ 0 ] :
		( ( block % block_sizes [ 1 ] ) == 0 ) ? block_sizes [ 1 ] :
		( ( block % block_sizes [ 2 ] ) == 0 ) ? block_sizes [ 2 ] :
		block_sizes [ 3 ];

	return ( img_struct -> block );	
}

/* --- @calculate_pregap@ --- *
 *
 * Arguments:   @file_ptrs *fptrs@ = pointer struct of source and destination file
 *		@image_struct *img_struct@ = pointer struct of type image and pregap of image
 *
 * Returns:     Zeor on success, @-1@ on error.
 *
 * Use:         Return the detection of the image.
 */
off_t calculate_pregap ( file_ptrs* fptrs,  image_struct*  img_struct ) 
{
	unsigned char	buf [ 12 ];
	off_t		img_size ;
        off_t 		n_loop = 0;
	off_t		start = 32768; 
	off_t		cd_id_start = -1;
	off_t		cd_id_end = 0;
	int		header = 0;

	/* SYNCH HEADER */
	unsigned const char HEADER_ID [ 12 ] = { 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00 };
	
	/* SCD/VCD Signature */
	unsigned const char XA_ID [ 8 ] = { 0x43, 0x44, 0x2D, 0x58, 0x41, 0x30, 0x30, 0x31 };
	
	/* Signature for Image ISO-9660 */
	unsigned const char ISO_9660_START [ 8 ] = { 0x01, 0x43, 0x44, 0x30, 0x30, 0x31, 0x01, 0x00 };
	unsigned const char ISO_9660_END [ 8 ] = { 0xFF, 0x43, 0x44, 0x30, 0x30, 0x31, 0x01, 0x00 };


	img_struct -> type = 0;
	img_size = get_file_size ( fptrs -> fsource ) ; 
	
	for ( n_loop = start ; n_loop < img_size; n_loop++ )
	{
		set_file_pointer ( fptrs -> fsource, n_loop );
		fread ( buf, sizeof ( char ), 12, fptrs -> fsource );
	
		if ( !memcmp ( HEADER_ID, buf, 12 ) ) {
			if ( ( img_struct -> type == 0 ) || ( img_struct -> type == 2 ) ) {
				img_struct -> type += 1;
			}
		
			if ( ( header != 16 ) && ( header != 24 ) )
				header += 16;
		} 
		else if ( !is_svcd_sub_header ( (unsigned char*) buf ) ) {
			if ( (	img_struct -> type == 0 ) || ( img_struct -> type == 2 ) ) {
				img_struct -> type += 1;
			}
			
			if ( ( header != 8 ) && ( header != 24 ) )
				header += 8;
			 
		} else 
			if ( !is_udf_image ( ( unsigned char *) buf ) ) {
				if ( cd_id_start < 0 ) {
					cd_id_start = n_loop;
					img_struct -> type +=2;
				} else {
					cd_id_end = n_loop;
					n_loop = img_size;
				}
			
			/*if ( !memcmp ( ISO_9660_START, buf, 8 ) ) {
			cd_id_start = n_loop;
			n_loop += 1023;
			img_struct -> type += 2;
		} else if ( !memcmp ( ISO_9660_END, buf, 8 ) ) {
			cd_id_end = n_loop;
			n_loop = img_size;
		*/
		
		} else if ( !memcmp ( XA_ID, buf, 8 ) ) { 
			if ( img_struct -> type <= 7 )
				img_struct -> type += 7;
		}
	}
		
	/* Detect Block of image */	
	img_struct -> block  = calculate_block_size ( cd_id_start, cd_id_end, img_struct );
	
	/* Detect Header bytes */
	img_struct -> pregap = calculate_pregap_length ( cd_id_start, img_struct , header );

	return ( 0 );	
}


