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
#define MKTOC_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef __cplusplus
extern "C" {
#endif  /* __cplusplus */

#ifndef MKCORE_H
#include "mkcore.h"
#endif



/*
#define TOC_AUDIO 		0
#define TOC_MODE1 		1
#define TOC_MODE1_RAW		2
#define TOC_MODE2		3
#define TOC_MODE2_FORM1		4
#define TOC_MODE2_FORM2		5
#define TOC_MODE2_FORM_MIX 	6
#define TOC_MODE2_RAW		7

*/
/* --- @print_toc_time@ --- *
 *
 * Arguments:   @file_ptrs *fptrs@ = input file
 * 		@struct_toc *toc@ =  pointer struct of toc sheet
 *
 *
 * Returns:	---
 *
 * Use:	 	print time of image.
 */
void print_toc_time ( file_ptrs* fptrs, struct_toc *toc );

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
void print_toc_mode ( file_ptrs* fptrs, struct_toc* toc, image_struct* img_struct );

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
void print_toc_datafile ( file_ptrs* fptrs, char* file_input );

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
void print_toc_track ( file_ptrs* fptrs, struct_toc* toc );

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
				off_t l_loop, off_t loop_last);

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
void toc_first_track ( file_ptrs* fptrs, image_struct* img_struct, char *file_input, struct_toc* toc );

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
void create_raw_toc  ( file_ptrs* fptrs, image_struct* img_struct, char *file_input );

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
void create_iso_toc ( file_ptrs* fptrs, image_struct* img_struct, char *file_input );

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
int create_vcd_toc ( file_ptrs* fptrs, image_struct* img_struct, char *file_input );


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
int create_toc ( file_ptrs* fptrs, image_struct* img_struct, char *file_input );


#ifdef __cplusplus
}       /* extern "C" */
#endif  /* __cplusplus */

#endif /* MKTOC_H */
