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

#ifndef MKTOC_H
#include "mktoc.h"
#endif

/* --- @print_toc_time@ --- *
 *
 * Arguments:   @file_ptrs *fptrs@ = input file
 * 		@struct_toc *toc@ =  pointer struct of toc 
 *
 *
 * Returns:	---
 *
 * Use:	 	print time of image.
 */
void print_toc_time ( file_ptrs* fptrs, struct_toc *toc )
{
	fprintf ( fptrs->fdesc, " %02d:%02d:%02d", toc->minute ,  toc->second-2, toc->frame );	
}

/* --- @print_toc_mode@ --- *
 *
 * Arguments:   @file_ptrs *fptrs@ = input file
 *		@struct_toc *toc@ = pointer struct of toc
 * 		@image_struct *img_struct@ = pointer struct of type image and pregap of image
 *
 *
 * Returns:	---
 *
 * Use:         read first block of image and  print type of mode.
 */
void print_toc_mode ( file_ptrs* fptrs, struct_toc* toc, image_struct* img_struct )
{
	switch ( ( img_struct-> block ) ) {
		case 2048:
			fprintf ( fptrs->fdesc, "\n" );
			break;
		case 2336:
			fprintf ( fptrs->fdesc, "_FORM_MIX\n");
			break;
		case 2352:
			fprintf ( fptrs->fdesc, "_RAW\n" );
			break;
		case 2448:
			fprintf ( fptrs->fdesc, "_RAW RW_RAW\n");
			break;
		default:
			break;
	}

}

/* --- @print_toc_datafile@ --- *
 *
 * Arguments:   @file_ptrs *fptrs@ = input file
 *		@char *file_input@  =  name of input file
 *
 *
 * Returns:     ---
 *
 * Use:         print name of datafile.
 */
void print_toc_datafile ( file_ptrs* fptrs, char* file_input )
{
	fprintf ( fptrs->fdesc, "DATAFILE \"%s\"", file_input );
}

/* --- @print_toc_track@ --- *
 *
 * Arguments:   @file_ptrs *fptrs@ = input file
 *		@struct_toc *toc@ = pointer struct of toc
 *
 *
 * Returns:     ---
 *
 * Use:         print track of image.
 */
void print_toc_track ( file_ptrs* fptrs, struct_toc* toc )
{
	fprintf( fptrs->fdesc, "TRACK MODE%d", toc->mode  );
}


/* --- @print_toc_vcd_time@ --- *
 *
 * Arguments:   @file_ptrs *fptrs@ = input file
 *		@struct_toc *toc@ = pointer struct of toc
 *		@image_struct *img_struct@ = pointer struct of type image and pregap of image
 * 		@off_t l_loop@ = length of track;
 *		@off_t loop_last@ = loop end last track;
 *
 *
 * Returns:     ---
 *
 * Use:         print time of track. 
 */

void print_toc_vcd_time ( file_ptrs* fptrs, struct_toc* toc, image_struct* img_struct, 
				off_t l_loop, off_t loop_last)
{
	msf_mode_block		msf_block;

	if ( ( loop_last * img_struct-> block ) > 0 )	
		fprintf ( fptrs-> fdesc , "\t#%d",  ( loop_last * img_struct->block ) );
			
	lba2msf (  l_loop, &msf_block );
		
	toc->frame =  ( *( msf_block.frame ) ) ;
	toc->second = ( *(  msf_block.second ) );
	toc->minute = ( *( msf_block.minute ) );

	print_toc_time ( fptrs, toc ); 

	fprintf ( fptrs->fdesc, " // length in bytes: %d\n", ( l_loop * img_struct->block ) );

}

/* --- @toc_first_track@ --- *
 *
 * Arguments:   @file_ptrs *fptrs@ = input file
 * 		@image_struct *img_struct@ = pointer struct of type image and pregap of image
 *		@char *file_input@  =  name of input file
 *		@struct_toc *toc@ = pointer struct of cuesheet
 *
 * Returns:     ---
 *
 * Use:         detect track of image.
 */
void toc_first_track ( file_ptrs* fptrs, image_struct* img_struct, char *file_input, struct_toc* toc )
{	
	off_t lba = 0;
	
	msf_mode_block msf_block;
	
	/* inizialization first track */
	toc->mode = is_mode ( fptrs, img_struct );
	toc->block = img_struct->block;

	toc->track = 1;
/*	toc->index = 1; */

	fprintf ( fptrs->fdesc, "// TRACK %d\n", toc->track );

	print_toc_track ( fptrs, toc );	

	print_toc_mode ( fptrs, toc, img_struct );
	
	print_toc_datafile ( fptrs, file_input );		

}
/* --- @create_raw_toc@ --- *
 *
 * Arguments:   @file_ptrs *fptrs@ = input file
 * 		@image_struct *img_struct@ = pointer struct of type image and pregap of image
 *		@char *file_input@  = name of input file
 *		
 *
 *
 * Returns:     ---
 *
 * Use:         generate a toc for raw image.
 */
void create_raw_toc  ( file_ptrs* fptrs, image_struct* img_struct, char *file_input )
{
	struct_toc toc;

	toc_first_track  ( fptrs, img_struct, file_input, &toc );

}

/* --- @create_iso_toc@ --- *
 *
 * Arguments:   @file_ptrs *fptrs@ = input file
 * 		@image_struct *img_struct@ = pointer struct of type image and pregap of image
 *		@char *file_input@  = name of input file
 *		
 *
 *
 * Returns:     ---
 *
 * Use:         generate a cuesheet for iso/udf image.
 */
void create_iso_toc ( file_ptrs* fptrs, image_struct* img_struct, char *file_input )
{
	struct_toc toc;

	toc_first_track ( fptrs, img_struct, file_input, &toc );

}
/* --- @create_vcd_toc@ --- *
 *
 * Arguments:   @file_ptrs *fptrs @ = input file
 * 		@image_struct *img_struct@ = pointer struct of type image and pregap of image
 *		@char *file_input@  = name of input file
 *
 *
 * Returns:     Zeor on success, @-1@ on error.
 *
 * Use:         generate a TOC file for vcd.
 */
int create_vcd_toc ( file_ptrs* fptrs, image_struct* img_struct, char *file_input )
{
	off_t n_loop;
	off_t loop_cur = 0;
	off_t loop_last = 0;
	off_t l_loop;
	off_t n_img_size;

	struct_toc 		toc;
	msf_mode_block		msf_block;
	
	if ( ( n_img_size = get_file_size ( fptrs -> fsource ) ) < 1 ) return ( -1 ); /* The image file is empty */
	
	toc_first_track  ( fptrs, img_struct, file_input, &toc );

	n_loop = img_struct->pregap ;
	
	while ( n_loop <  n_img_size ) {

		progress_bar ( ( int ) ( ( ( n_loop + 1 ) * 100 ) / n_img_size ) );

		if ( track_vcd ( fptrs, img_struct, &toc, n_loop ) == AOK ) {
			
			toc.track++;
	
			l_loop  = loop_cur - loop_last;
							
			print_toc_vcd_time  ( fptrs, &toc, img_struct, l_loop, loop_last);
			
			fprintf ( fptrs->fdesc, "// TRACK %d\n", toc.track );
			
			print_toc_track ( fptrs, &toc ); 

			print_toc_mode ( fptrs, &toc, img_struct );

			print_toc_datafile ( fptrs, file_input );		
			
			loop_last = loop_cur;
		
		}
				

		loop_cur++;

		n_loop += img_struct->block;

	}

	l_loop = loop_cur - loop_last;

	print_toc_vcd_time  ( fptrs, &toc, img_struct, l_loop, loop_last);
	
	progress_bar ( 100 );

	return ( 0 );
}

/* --- @create_toc@ --- *
 *
 * Arguments:   @file_ptrs *fptrs @ = input file
 * 		@image_struct *img_struct@ = pointer struct of type image and pregap of image
 *		@char *file_input@  = name of input file
 *		
 *
 * Returns:     Zeor on success, @-1@ on error.
 *
 * Use:         Get info from file for generate a TOC file descriptor.
 */
int create_toc ( file_ptrs* fptrs, image_struct* img_struct, char *file_input )
{
	int     n_return_value = AOK;

	fprintf( fptrs->fdesc, "// Generated with %s v%s\n", PACKAGE_NAME, VERSION );


	
	switch (  img_struct->type  )	{
		case IMG_AUDIO:
			fprintf ( fptrs->fdesc, "CD_DA\n" );
			printf ("Need implementation\n");
			break;
		case IMG_ISO:
			fprintf ( fptrs->fdesc, "CD_ROM\n" ); 
			create_iso_toc ( fptrs, img_struct, file_input );
			break;
		case IMG_RAW:
			fprintf ( fptrs->fdesc, "CD_ROM\n" );
			create_raw_toc ( fptrs, img_struct, file_input ); 
			break;
		case IMG_VCD: case 9  : case 10 :
			fprintf ( fptrs->fdesc, "CD_ROM_XA\n");	
			create_vcd_toc ( fptrs, img_struct, file_input ); 
			break;
		default :
			n_return_value = ERROR;
			break;
	}
	return ( n_return_value );
}


