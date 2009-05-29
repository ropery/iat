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

/* --- @img_2_bin@ --- *
 *
 * Arguments:   @file_ptrs *fptrs@ = input file
 * 		@int block_old@ = size of origin block
 *		@int block_new@ = size of new block
 *		@off_t pregap@ = length of pregap
 *
 *
 * Returns:	mode of image, @-1@ otherwise
 *
 * Use:		convert image to image as compatible for cuesheet file. 
 */
img_2_bin ( file_ptrs* fptrs,  int block_old, int block_new, off_t pregap )
{
        int	n_return_value = ERROR;
	char	*fimg =  malloc ( sizeof (char) * block_old); 
	off_t	n_loop;
	off_t	n_img_size;				


	if ( ( n_img_size = get_file_size ( fptrs -> fsource ) ) < 1 ) return ( n_return_value ); /* The image file is empty */


	set_file_pointer ( fptrs -> fsource, pregap );


		for ( n_loop = pregap  ; n_loop <  n_img_size ; n_loop += block_old ) {
       			progress_bar ( ( ( n_loop + 1 ) * 100 ) / n_img_size );
                	fread  ( fimg , 1, block_old, fptrs -> fsource );	
			fwrite ( fimg, 1, block_new, fptrs -> fdest );
		}

	free ( fimg );	

	progress_bar ( 100 );
	return ( 0 );
}

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

/* --- @print_cue@ --- *
 *
 * Arguments:   @file_ptrs *fptrs@ = input file
 * 		 @struct_cue *cue@ =  pointer struct of cue sheet
 *
 *
 * Returns:	mode of image, @-1@ otherwise
 *
 *  Use:	print cue sheet of image.	
 */
int print_cue ( file_ptrs* fptrs, struct_cue* cue )
{
	fprintf( fptrs->fdesc, "TRACK %02d MODE%d/%d\n",  cue->track , cue->mode, cue->block  );
	fprintf( fptrs->fdesc, " INDEX %d %02d:%02d:%02d\n", cue->index , cue->minute ,  cue->second-2, cue->frame );	
}

/* --- @is_mode@ --- *
 *
 * Arguments:   @file_ptrs *fptrs @ = input file
 * 		@image_struct *img_struct@ = pointer struct of type image and pregap of image
 *
 *
 * Returns:	mode of image, @-1@ otherwise
 *
 * Use:         read first block of image and return type of mode.
 */
int is_mode ( file_ptrs* fptrs, image_struct* img_struct )
{
	int mode = -1;
	off_t n_loop;

	msf_mode_block	msf_block;
	
	switch ( ( img_struct-> block ) ) {
		case 2048:
			mode = 1;
			break;
		case 2336:
			mode = 2;
			break;
		case 2352:
		case 2448:	
			n_loop = img_struct -> pregap + 12;

			set_file_pointer ( fptrs -> fsource, ( n_loop  ) );

			fread ( &msf_block, sizeof ( msf_mode_block ), 1,  fptrs->fsource );
			switch  ( *( msf_block.mode ) ) {
				case 0: 
					mode = 0;
					break;
				case 1:
					mode = 1;
					break;
				case 2:
					mode = 2;
					break;
				default:
					break;
			}

			break;
			
		default:
			break;
	}
	
	return ( mode );
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
int create_first_track ( file_ptrs* fptrs, image_struct* img_struct, char *file_input, struct_cue* cue )
{	
	off_t lba = 0;
	
	msf_mode_block msf_block;
	
	/* inizialization first track */
	cue->mode = is_mode ( fptrs, img_struct );
	cue->block = img_struct->block;

	if ( cue->block == 2448 )
		cue->block = 2352;
	
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
int create_raw_cue ( file_ptrs* fptrs, image_struct* img_struct, char *file_input )
{

	struct_cue cue;


	if ( ( fptrs->fdest ) ) {
		
		img_2_bin ( fptrs,  img_struct->block, 2352, img_struct->pregap );
		
	};

	create_first_track ( fptrs, img_struct, file_input, &cue );	

	return ( 0 );
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
int create_iso_cue ( file_ptrs* fptrs, image_struct* img_struct, char *file_input )
{
	struct_cue cue;

	if ( fptrs->fdest ) 
		img_2_bin ( fptrs,  img_struct->block, 2048, img_struct->pregap );

	create_first_track ( fptrs, img_struct, file_input, &cue );	
	
	return ( 0 );

}

/* --- @track_vcd_cue@ --- *
 *
 * Arguments:   @file_ptrs *fptrs @ = input file
 * 		@image_struct *img_struct@ = pointer struct of type image and pregap of image
 *		@struct_cue *cue@ = pointer struct of cuesheet
 *		@off_t n_loop@  = number of byte from where the block starts
 *
 *
 * Returns:     ---
 *
 * Use:         detect track of VCD/SVCD image.
 */
int track_vcd_cue ( file_ptrs* fptrs, image_struct* img_struct, struct_cue* cue, off_t n_loop )
{
	int     n_return_value = ERROR;
	static int file_number = 1;
	
	copy_sub_header		copy_header;

	
	switch ( img_struct->block ) {
		case 2352:
			n_loop +=16;
		case 2336:
			set_file_pointer ( fptrs -> fsource, ( n_loop ) );
			
			fread ( &copy_header, 1, sizeof ( copy_sub_header ), fptrs -> fsource );
			/* new file number + real time mode = new track */	
			if ( (  file_number  == ( *( copy_header.file ) ) )  && ( SUB_MODE_RT & ( *( copy_header.sub_mode ) ) ) ) {
				file_number++;				
				n_return_value = AOK;	
			}
		default:
			break;
			
	}


	return ( n_return_value );

}
/* --- @create_vcd_cue@ --- *
 *
 * Arguments:   @file_ptrs *fptrs @ = input file
 * 		@image_struct *img_struct@ = pointer struct of type image and pregap of image
 *		@char *file_input@  = name of input file
 *
 *
 * Returns:     ---
 *
 * Use:         generate a cuesheet for vcd.
 */
int create_vcd_cue ( file_ptrs* fptrs, image_struct* img_struct, char *file_input )
{
	off_t n_loop;
	off_t img_size;
	int number_block = 0;	

	int block = 2352;

	struct_cue 		cue;
	msf_mode_block		msf_block;
	
	if ( ( img_size = get_file_size ( fptrs -> fsource ) ) < 1 ) return ( -1 ); /* The image file is empty */
	
	if ( img_struct -> block > 2352 ) 
		block = 2352;
		else  block = img_struct -> block;
	
	if ( ( fptrs->fdest ) ) {
		
		img_2_bin ( fptrs,  img_struct->block, block, img_struct->pregap );
		
	};

	
	create_first_track  ( fptrs, img_struct, file_input, &cue );

	n_loop = img_struct->pregap ;
	
	while ( n_loop <  img_size ) {

		
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

	n_loop += img_struct->block;

	}
	return ( 0 );
}

/* --- @create_cue@ --- *
 *
 * Arguments:   @file_ptrs *fptrs @ = input file
 * 		@image_struct *img_struct@ = pointer struct of type image and pregap of image
 *		@char *file_input@  = name of input file
 *		
 *
 * Returns:     ---
 *
 * Use:         Get info from file for generate a cuesheet file descriptor.
 */
int create_cue ( file_ptrs* fptrs, image_struct* img_struct, char *file_input )
{
	fprintf( fptrs->fdesc, "REM Generated with %s v%s\n", PACKAGE_NAME, VERSION );

	set_file_pointer ( fptrs -> fsource, ( img_struct -> pregap ) );


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
			printf ("Error\n");
			break;
	}
	return ( 0 );
}



