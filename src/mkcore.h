/**
 * Copyright (C) 2009 
 *	- Salvatore Santagati <salvatore.santagati@gmail.com>
 *	- Abdur Rab <c.abdur@yahoo.com>
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

#ifndef MKCORE_H
#define MKCORE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef __cplusplus
extern "C" {
#endif  /* __cplusplus */

#ifndef DEFINE_H
#include "define.h"
#endif

#ifndef UTIL_H
#include "util.h"
#endif

#ifndef MMC2R11_H
#include "mmc2r11.h"
#endif

typedef struct struct_descriptor {
	char *file;
	int track;
	int mode;
	int block;
	int index;
	int minute;
	int second;
	int frame;
} struct_cue, struct_toc;

/* --- @is_valid_block@ --- *
 *
 * Arguments:   @int  *number@  = pointer of number of block compatible.
 *		@size_t *block_sizes@ = pointer vector of block compatible.
 *		@size_t *block@ = pointer block of image.
 *
 *
 * Returns:	Zeor on success, @-1@ on error.
 *
 * Use:	 	check if is valid block for file descriptor
 *
 */

int  is_valid_fd_block ( int* number, size_t* block_sizes, size_t* block  );


/* --- @is_mode@ --- *
 *
 * Arguments:   @file_ptrs *fptrs @ = input file
 * 		@image_struct *img_struct@ = pointer to struct of image information
 *
 * Returns:	mode of image, @-1@ otherwise
 *
 * Use:         read first block of image and return type of mode.
 */
int is_mode ( file_ptrs* fptrs, image_struct* img_struct );

/* --- @track_vcd@ --- *
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
int track_vcd ( file_ptrs* fptrs, image_struct* img_struct, struct_cue* cue, off_t n_loop );

#ifdef __cplusplus
}       /* extern "C" */
#endif  /* __cplusplus */

#endif /* MKCORE_H */
