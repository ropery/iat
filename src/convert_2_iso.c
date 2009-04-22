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

#ifndef CONVERT_2_ISO_H
#include "convert_2_iso.h"
#endif

/* --- @print@ --- *
 *
 * Temporary function, will be removed in the release
 */
void print ( unsigned char* ptr, int n_len ) 
{
	int n_loop = 0;
	if ( n_len > 16 ) {
		printf ("Data :");
		for ( n_loop = 0; n_loop < n_len; n_loop++ ) {
			printf ("%X", (unsigned char) *( ptr + n_loop ) );
		}
		printf ("\n\n");
	} else if ( n_len > 0 ) {
		printf ("2 BYTE :");
		for ( n_loop = 0; n_loop < n_len; n_loop++ ) {
			printf ("|%2X|", (unsigned char) *( ptr + n_loop ) );
		}
		printf ("\n\n");
	}
}

/* --- @write_2_file@ --- *
 *
 * Arguments:	@FILE *fptr@ = pointer to FILE
 * 		@unsigned char* buf_ptr@ = pointer to buffer to be written to file
 * 		@size_t n_len@ = length of bytes to be written
 *
 * Returns:	size written in the file, @-1@ otherwise
 *
 * Use:		Write to an iso file.
 */
long write_2_file ( FILE* fptr, unsigned char* buf_ptr, size_t n_len )
{
	if ( ( n_len < 1 ) || ( NULL == fptr ) || ( NULL == buf_ptr ) ) return ( -1 );
	return ( ( long ) fwrite ( buf_ptr, sizeof ( unsigned char ), n_len, fptr ) );
}

/* --- @progress_bar@ --- *
 *
 * Arguments:	@int percentage@ = percentage value
 *
 * Returns:	---
 *
 * Use:		Displays a command line progress bar.
 */
void progress_bar ( int percentage )
{
	char		roller [ ] = { "-\\|/" }; /* For the processing */
	char		roller_ch = 0; /* Progress roller */
	char		arrow_head = 0; /* Progress arrow */
	static int	previous_percentage = -1; /* Previous percentage */

	if ( percentage == previous_percentage ) return;  /* Nothing changed */
	if ( percentage == 100 ) {
		previous_percentage = -1;
		roller_ch = ' ';
		arrow_head = '=';
	} else {
		previous_percentage = percentage;
		roller_ch = roller [ ( percentage % 4 ) ];
		arrow_head = '>';
	}
	
	printf("%c%3d%% [:%.*s%c%.*s:]\r", roller_ch, percentage, ( percentage / 5 ), 
			"====================", arrow_head, ( 20 - ( percentage / 5 ) ),"                    ");
	fflush ( stdout );
}

/* --- @mode_0@ --- *
 *
 * Arguments:	@file_ptrs *fptrs@ = pointer struct of source and destination file
 * 		@long n_fptr_pos@ = the position of byte from where to be read
 *
 * Returns:	the number of bytes read, @-1@ otherwise
 *
 * Use:		Reads into the buffer and writes the buffer to destination file.
 */
long mode_0 ( file_ptrs* fptrs, long n_fptr_pos )
{
	/* Mode 0 (2352): Syncheader (12), MSF / BCD (3), Mode (1), Data (2336) */
	mode_generic		mgen; /* Mode 0 and Mode 2 Formless */

	/*printf ( "Mode Empty / Mode 2 Formless\n" );*/
	memset ( &mgen, 0, sizeof ( mode_generic ) );
	fread ( &mgen, 1, sizeof ( mode_generic ), fptrs -> fsource );
	write_2_file ( fptrs -> fdest, ( void* ) &mgen.user_data, 2336 );

	return ( sizeof ( mode_generic ) );
}

/* --- @mode_1@ --- *
 *
 * Arguments:	@file_ptrs *fptrs@ = pointer struct of source and destination file
 * 		@long n_fptr_pos@ = the position of byte from where to be read
 *
 * Returns:	the number of bytes read, @-1@ otherwise
 *
 * Use:		Reads into the buffer and writes the buffer to destination file.
 */
long mode_1 ( file_ptrs* fptrs, long n_fptr_pos )
{
	/* Mode 1 (2352): Syncheader (16), Data (2048), CRC (4), Subheader (8), ECC (276) */
	mode_one		mone; /* Mode 1 */
	
	/*printf ( "Mode 1\n" );*/
	memset ( &mone, 0, sizeof ( mode_one ) );
	fread ( &mone, 1, sizeof ( mode_one ), fptrs -> fsource );
	write_2_file ( fptrs -> fdest, ( void* ) &mone.user_data, 2048 );

	return ( sizeof ( mode_one ) );
}

/* --- @mode_2_form_1@ --- *
 *
 * Arguments:	@file_ptrs *fptrs@ = pointer struct of source and destination file
 * 		@long n_fptr_pos@ = the position of byte from where to be read
 *
 * Returns:	the number of bytes read, @-1@ otherwise
 *
 * Use:		Reads into the buffer and writes the buffer to destination file.
 */
long mode_2_form_1 ( file_ptrs* fptrs, long n_fptr_pos )
{
	/* Mode 2 Form 1 (2352): Syncheader (16), Subheader (8), Data (2048), ECC (280) */
	mode_two_form_1		m2f1; /* Mode 2 Form 1 */

	/*printf ( "Mode 2 Form 1\n" );*/
	memset ( &m2f1, 0, sizeof ( mode_two_form_1 ) );	
	fread ( &m2f1, 1, sizeof ( mode_two_form_1 ), fptrs -> fsource );
	write_2_file ( fptrs -> fdest, ( void* ) &m2f1.user_data, 2048 );

	return ( sizeof ( mode_two_form_1 ) );
}

/* --- @mode_2_form_2@ --- *
 *
 * Arguments:	@file_ptrs *fptrs@ = pointer struct of source and destination file
 * 		@long n_fptr_pos@ = the position of byte from where to be read
 *
 * Returns:	the number of bytes read, @-1@ otherwise
 *
 * Use:		Reads into the buffer and writes the buffer to destination file.
 */
long mode_2_form_2 ( file_ptrs* fptrs, long n_fptr_pos )
{
	/* Mode 2 Form 2 (2352): Syncheader (16), Subheader (8), Data (2324), CRC (4) */
	mode_two_form_2		m2f2; /* Mode 2 Form 2 */

	/*printf ( "Mode 2 Form 2\n" );*/
	memset ( &m2f2, 0, sizeof ( mode_two_form_2 ) );
	fread ( &m2f2, 1, sizeof ( mode_two_form_2 ), fptrs -> fsource );
	write_2_file ( fptrs -> fdest, ( void* ) &m2f2.user_data, 2324 );

	return ( sizeof ( mode_two_form_2 ) );
}

/* --- @mode_2@ --- *
 *
 * Arguments:	@file_ptrs *fptrs@ = pointer struct of source and destination file
 * 		@long n_fptr_pos@ = the position of byte from where to be read
 *
 * Returns:	the number of bytes read, @-1@ otherwise
 *
 * Use:		Reads into the buffer and writes the buffer to destination file.
 */
long mode_2 ( file_ptrs* fptrs, long n_fptr_pos )
{
	int n_mode = 0;
	sub_header_block	sub_header; /* Sub Header */
	long (* mode_form [ 3 ] ) ( file_ptrs* fptrs, long n_fptr_pos ) = { &mode_2_form_1, &mode_2_form_2, &mode_0 };

	memset ( &sub_header, 0, sizeof ( sub_header_block ) );

	/* Move the file pointer to read the sub-header info */
	set_file_pointer ( fptrs -> fsource, ( n_fptr_pos += ( long ) sizeof ( sync_header_block ) ) );

	fread ( &sub_header, 1, sizeof ( sub_header_block ), fptrs -> fsource );

	/* Revert back the file pointer as it has moved  
	 * till the sub-header (read 16 + 8 bytes of data) */
	set_file_pointer ( fptrs -> fsource, ( n_fptr_pos -= ( long ) sizeof ( sync_header_block ) ) );

	if ( !memcmp ( sub_header.first_copy, sub_header.second_copy, 4 ) ) {
		/* Values { 0, 32, etc.. } 32 (5th bit set - Form 2), 0 - (5th bit not set - Form 1)*/
		n_mode = ( ( n_mode = ( ( (int) *( sub_header.first_copy + 2 ) ) & 0x20 ) ) == 32 ) ? 1 : ( n_mode == 0 ) ? 0 : 2;
		n_fptr_pos = ( *( mode_form [ n_mode ] ) ) ( fptrs, n_fptr_pos );
	} else {
		/* It is Formless */
		/* Mode 2 (2352): Syncheader (12), MSF / BCD (3), Mode (1), Data (2336) */
		n_fptr_pos = ( *( mode_form [ 2 ] ) ) ( fptrs, n_fptr_pos );
	}

	return ( n_fptr_pos );
}

/* --- @mode_2_form_1_headerless@ --- *
 *
 * Arguments:	@file_ptrs *fptrs@ = pointer struct of source and destination file
 * 		@long n_fptr_pos@ = the position of byte from where to be read
 *
 * Returns:	the number of bytes read, @-1@ otherwise
 *
 * Use:		Reads into the buffer and writes the buffer to destination file.
 */
long mode_2_form_1_headerless ( file_ptrs* fptrs, long n_fptr_pos )
{
	/* Image has Sub Header alone */
	/* Mode 2 (2336): Subheader (8), Data (2048), ECC (280) */
	mode_two_form_1_headerless	mtwo; /* Mode 2 with 8 byte header */

	/*printf ( "Mode 2 Data Format\n" );*/
	memset ( &mtwo, 0, sizeof ( mode_two_form_1_headerless ) );
	fread ( &mtwo, 1, sizeof ( mode_two_form_1_headerless ), fptrs -> fsource );
	write_2_file ( fptrs -> fdest, ( void* ) &mtwo.user_data, 2048 );

	return ( sizeof ( mode_two_form_1_headerless ) );
}

/* --- @mode_2_form_2_headerless@ --- *
 *
 * Arguments:	@file_ptrs *fptrs@ = pointer struct of source and destination file
 * 		@long n_fptr_pos@ = the position of byte from where to be read
 *
 * Returns:	the number of bytes read, @-1@ otherwise
 *
 * Use:		Reads into the buffer and writes the buffer to destination file.
 */
long mode_2_form_2_headerless ( file_ptrs* fptrs, long n_fptr_pos )
{
	/* Image has Sub Header alone */
	/* Mode 2 (2336): Subheader (8), Data (2324), CRC (4) */
	mode_two_form_2_headerless	mtwo; /* Mode 2 with 8 byte header */

	/*printf ( "Mode 2 Data Format\n" );*/
	memset ( &mtwo, 0, sizeof ( mode_two_form_2_headerless ) );
	fread ( &mtwo, 1, sizeof ( mode_two_form_2_headerless ), fptrs -> fsource );
	write_2_file ( fptrs -> fdest, ( void* ) &mtwo.user_data, 2324 );

	/*print ( ( void* ) &mtwo.user_data, 2328 );
	print ( ( void* ) ( ( mtwo.user_data + 2319 ) ), 8 );*/

	return ( sizeof ( mode_two_form_2_headerless ) );
}

/* --- @bin_2_iso@ --- *
 *
 * Arguments:	@file_ptrs *fptrs@ = pointer struct of source and destination file
 * 		@image_struct *img_struct@ = struct of image pregap
 *
 * Returns:	Zeor on success, @-1@ on error.
 *
 * Use:		Return the detection of the image.
 */
int bin_2_iso ( file_ptrs* fptrs,  image_struct*  img_struct )
{
	long	n_loop = 0;
	long	n_img_size = 0;
	int	n_return_value = ERROR;
	int	n_mode = 0;

	unsigned const char synch_pattern [ 12 ] = { 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00 };
/*	unsigned const char pdi_header [ 16 ] = { 0x54, 0x54, 0x41, 0x46, 0x4D, 0x50, 0x56, 0x4F, 0x42, 0x43, 0x44, 0x49, 0x4D, 0x47, 0x01, 0x00 };
*/
	sync_header_block	header; /* Sync Header Block */

	long (* mode [ 5 ] ) ( file_ptrs* fptrs, long n_fptr_pos ) = { &mode_0, &mode_1, &mode_2, &mode_2_form_1_headerless, &mode_2_form_2_headerless };
	

	if ( NULL== fptrs -> fsource ) return ( n_return_value ); /* The source file pointer is empty */
	if ( ( n_img_size = get_file_size ( fptrs -> fsource ) ) < 1 ) return ( n_return_value ); /* The image file is empty */
	/*if ( ( n_img_size = bin_image_size ( fptrs -> fsource ) ) < 1 ) return ( n_return_value );*/  /* The image file is empty */

	for ( n_loop = img_struct -> pregap ; n_loop < n_img_size; ) {

		progress_bar ( ( ( n_loop + 1 ) * 100 ) / n_img_size );

		/* Initalize for the loop */
		memset ( &header, 0, sizeof ( sync_header_block ) );
		
		/* Initialize the file pointer to the start point */
		set_file_pointer ( fptrs -> fsource, n_loop );
		
		fread ( &header, 1, sizeof ( sync_header_block ), fptrs -> fsource );

		/*
		printf ("Image size :%ld\tLoop No :%ld\n\n", n_img_size, n_loop );		
		print ( ( void* ) &header, 8 );
		*/

		/* Revert back the file pointer as it has moved the 
		 * file pointer till the header (read 16 bytes of data) */
		set_file_pointer ( fptrs -> fsource, n_loop );

		if ( !memcmp ( &synch_pattern, &header, 12 ) ) {
			/* Image has 12 BYTE SYNC HEADER */
			n_mode = ( (char) ( *( header.msf_block.mode ) ) );
			if ( ( n_mode > -1 ) && ( n_mode < 3 ) )
				/* Mode { 0, 1, 2 } */
				n_loop += ( *( mode [ n_mode ] ) ) ( fptrs, n_loop ); /* Increment to the next block */
			else printf ( "Weird Mode \n" );
		} else if ( ( !memcmp ( &header, ( ( (unsigned char*) (&header) ) + 4 ), 4 ) ) ) {

			/*print ( ( void* ) &header, 8 );*/
			if ( !is_svcd_sub_header ( (unsigned char*) &header ) ) {
				/* Image has 8 BYTE HEADER with User Data 2048 */
				n_loop += ( *( mode [ 3 ] ) ) ( fptrs, n_loop ); /* Increment to the next block */
			} else {
				/* Image has 8 BYTE HEADER with User Data 2324 */
				n_loop += ( *( mode [ 4 ] ) ) ( fptrs, n_loop ); /* Increment to the next block */
			}
		}/* else if ( !memcmp ( &pdi_header, &header, 16 ) ) {
			n_loop += 304;  Skip the PDI Properatery Header 
		}*/ else {
			/* Image does not have any standard header */
			/*print ( ( void* ) &header, 16 );*/
			n_loop++; /* Increment to the next location */
		}
	}

	n_return_value = AOK;
	progress_bar ( 100 );

	return ( n_return_value );
}

/* --- @img_2_iso@ --- *
 *
 * Arguments:   @file_ptrs *fptrs@ = pointer struct of source and destination file
 *              @image_struct *img_struct@ = struct of image pregap
 *
 * Returns:     Zeor on success, @-1@ on error.
 *
 * Use:         Return the detection of the image.
 */

int img_2_iso ( file_ptrs* fptrs,  image_struct*  img_struct )
{
        long    	n_loop = 0;
        long    	n_img_size = 0;
	unsigned char*	data_buffer = 0;
        int     	n_return_value = ERROR;

	/*char	data [ 2048 ] ;*/

	if ( ( n_img_size = get_file_size ( fptrs -> fsource ) ) < 1 ) return ( n_return_value ); /* The image file is empty */
        
	set_file_pointer ( fptrs -> fsource, img_struct -> pregap );
	
	data_buffer = ( unsigned char* ) malloc ( sizeof ( unsigned char ) * ( img_struct -> block ) );
	if ( NULL != data_buffer ) {
		memset ( data_buffer, 0, img_struct -> block );
		for ( n_loop = img_struct -> pregap  ; n_loop <  n_img_size ; n_loop += img_struct -> block ) {
        	        progress_bar ( ( ( n_loop + 1 ) * 100 ) / n_img_size );
                	fread ( data_buffer , sizeof ( char ),  img_struct -> block, fptrs -> fsource );	
			write_2_file ( fptrs -> fdest, ( void* ) data_buffer, img_struct -> block );
		}
		free ( data_buffer );
	}

	n_return_value = AOK;
	progress_bar ( 100 );
	
	return ( n_return_value );
}
