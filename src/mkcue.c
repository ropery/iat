/**
 * Copyright (C) 2009 
 *	- Salvatore Santagati <salvatore.santagati@gmail.com>
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

#ifndef MKCUE_H
#include "mkcue.h"
#endif

/* --- @print_cue_index@ --- *
 *
 * Arguments:   @file_ptrs *fptrs@ = input file
 * 		@struct_cue *cue@ =  pointer struct of cue sheet
 *
 *
 * Returns:	---	
 *
 * Use:	 	print index of image.
 */
void  print_cue_index ( file_ptrs* fptrs, struct_cue *cue )
{
	fprintf ( fptrs->fdesc, "\t\tINDEX %02d %02d:%02d:%02d\n", cue->index , cue->minute ,  cue->second-2, cue->frame );	
}

/* --- @print_cue_track@ --- *
 *
 * Arguments:   @file_ptrs *fptrs@ = input file
 * 		@struct_cue *cue@ =  pointer struct of cue sheet
 *
 *
 * Returns:	---
 *
 * Use:	 	print track of image.
 */
void print_cue_track ( file_ptrs* fptrs, struct_cue* cue )
{
	fprintf( fptrs->fdesc, "\tTRACK %02d MODE%d/%d\n",  cue->track , cue->mode, cue->block  );
}

/* --- @print_cue_file --- *
 *
 * Arguments:   @file_ptrs *fptrs@ = input file
 * 		@struct_cue *cue@ =  pointer struct of cue sheet
 *
 *
 * Returns:	---	
 *
 * Use:	 	print file name of image.
 */
void print_cue_file ( file_ptrs* fptrs, char *file_input )
{
	fprintf ( fptrs->fdesc, "FILE \"%s\" BINARY\n", file_input);
}

/* --- @create_first_track@ --- *
 *
 * Arguments:   @file_ptrs *fptrs @ = input file
 * 		@image_struct *img_struct@ = pointer struct of type image and pregap of image
 *		@char *file_input@  =  name of input file
 *		@struct_cue *cue@ = pointer struct of cuesheet
 *
 * Returns:     ---
 *
 * Use:         detect track of image.
 */
void create_first_track ( file_ptrs* fptrs, image_struct* img_struct, char *file_input, struct_cue* cue )
{	
	off_t lba = 0;
	
	msf_mode_block msf_block;

	if ( img_struct-> block == 2448 ) img_struct->block = 2352;
	
	/* inizialization first track */
	cue->mode = is_mode ( fptrs, img_struct );
	cue->block = img_struct->block;

	cue->track = 1;
	cue->index = 1;
	
	/* print cuesheet */	
	print_cue_file 	( fptrs, file_input );
	
	/* get time */
	lba2msf ( lba, &msf_block );
	cue->frame = ( *( msf_block.frame ) );
	cue->second = ( *(  msf_block.second ) );
	cue->minute = ( *( msf_block.minute ) );

	print_cue_track ( fptrs, cue ); 
	print_cue_index ( fptrs, cue );	

}
/* --- @create_raw_cue@ --- *
 *
 * Arguments:   @file_ptrs *fptrs @ = input file
 * 		@image_struct *img_struct@ = pointer struct of type image and pregap of image
 *		@char *file_input@  = name of input file
 *
 *
 * Returns:     ---
 *
 * Use:         generate a cuesheet for raw image.
 */
void create_raw_cue ( file_ptrs* fptrs, image_struct* img_struct, char *file_input )
{

	struct_cue cue;

	create_first_track ( fptrs, img_struct, file_input, &cue );	

}

/* --- @create_iso_cue@ --- *
 *
 * Arguments:   @file_ptrs *fptrs @ = input file
 * 		@image_struct *img_struct@ = pointer struct of type image and pregap of image
 *		@char *file_input@  = name of input file
 *		
 *
 *
 * Returns:     ---
 *
 * Use:         generate a cuesheet for iso/udf image.
 */
void create_iso_cue ( file_ptrs* fptrs, image_struct* img_struct, char *file_input )
{
	struct_cue cue;

	create_first_track ( fptrs, img_struct, file_input, &cue );	

}

/* --- @track_vcd_cue@ --- *
 *
 * Arguments:   @file_ptrs *fptrs @ = input file
 * 		@image_struct *img_struct@ = pointer struct of type image and pregap of image
 *		@struct_cue *cue@ = pointer struct of cuesheet
 *		@off_t n_loop@  = number of byte from where the block starts
 *
 *
 * Returns:     Zeor on success, @-1@ on error. 
 *
 * Use:         detect track of VCD/SVCD image.
 */
int track_vcd_cue ( file_ptrs* fptrs, image_struct* img_struct, struct_cue* cue, off_t n_loop )
{
	int     n_return_value = ERROR;
	
	if ( track_vcd ( fptrs, img_struct, cue, n_loop ) == AOK ) 
		n_return_value = AOK;
	

	return ( n_return_value );

}
/* --- @create_vcd_cue@ --- *
 *
 * Arguments:   @file_ptrs *fptrs @ = input file
 * 		@image_struct *img_struct@ = pointer struct of type image and pregap of image
 *		@char *file_input@  = name of input file
 *
 *
 * Returns:     Zeor on success, @-1@ on error.
 *
 * Use:         generate a cuesheet for vcd.
 */
int create_vcd_cue ( file_ptrs* fptrs, image_struct* img_struct, char *file_input )
{
	off_t n_loop;
	off_t n_img_size;
	off_t number_block = 0;

	struct_cue 		cue;
	msf_mode_block		msf_block;
	
	if ( ( n_img_size = get_file_size ( fptrs -> fsource ) ) < 1 ) return ( -1 ); /* The image file is empty */
	
	create_first_track  ( fptrs, img_struct, file_input, &cue );

	n_loop = img_struct->pregap ;
	
	while ( n_loop <  n_img_size ) {

		progress_bar ( ( int ) ( ( ( n_loop + 1 ) * 100 ) / n_img_size ) );

		if ( track_vcd_cue ( fptrs, img_struct, &cue, n_loop ) == AOK ) {
			cue.track++;
			
			lba2msf ( number_block, &msf_block );
			 
			cue.frame = ( *( msf_block.frame ) );
			cue.second = ( *(  msf_block.second ) );
			cue.minute = ( *( msf_block.minute ) );
		
			print_cue_track ( fptrs, &cue ); 
			print_cue_index ( fptrs, &cue );	
		
		}

		number_block++;

		n_loop += img_struct -> block;

	}
	
	progress_bar ( 100 );

	printf ( "\n" );

	return ( 0 );
}

/* --- @create_cue@ --- *
 *
 * Arguments:   @file_ptrs *fptrs @ = input file
 * 		@image_struct *img_struct@ = pointer struct of type image and pregap of image
 *		@char *file_input@  = name of input file
 *		
 *
 * Returns:     Zeor on success, @-1@ on error. 
 *
 * Use:         Get info from file for generate a cuesheet file descriptor.
 */
int create_cue ( file_ptrs* fptrs, image_struct* img_struct, char *file_input )
{
	int     n_return_value = AOK;

	if ( img_struct -> block <= 2448 ) {

		fprintf( fptrs->fdesc, "REM Generated with %s v%s\n", PACKAGE_NAME, VERSION );

		switch (  img_struct->type  )	{
			case IMG_AUDIO:
				printf ("Need implementation\n");
				break;
			case IMG_ISO:
				create_iso_cue ( fptrs, img_struct, file_input );
				break;
			case IMG_RAW:
				create_raw_cue ( fptrs, img_struct, file_input );
				break;
			case IMG_VCD: case 9  : case 10 :
				create_vcd_cue ( fptrs, img_struct, file_input );
				break;
			default :
				n_return_value = ERROR;
				printf ("Error\n");
				break;
		}
	}
	else n_return_value = ERROR;

	return ( n_return_value );
}



