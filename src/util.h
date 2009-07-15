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

#ifndef UTIL_H
#define UTIL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef __cplusplus
extern "C" {
#endif	/* __cplusplus */

#ifndef DEFINE_H
#include "define.h"
#endif


#ifndef MMC2R11_H
#include "mmc2r11.h"
#endif

/* ---@free_allocated_memory@ ---*
*
* Arguments:	@void* pointer_to_free@ = pointer to be freed
*
* Returns:	---
*
* Use:		Frees the allocated memory.
*
*/
void free_allocated_memory ( void* pointer_to_free );

/* ---@copy_string@ ---*
*
* Arguments:	@char* cp_string@ = pointer to string to be copied
*
* Returns:	The copied string if successful, @NULL@ otherwise.
*
* Use:		Copies the string to the newly allocated space.
*
*/
unsigned char* copy_string ( char* cp_string );

/* ---@smart_name@ ---*
*
* Arguments:	@char *new@ = pointer to new name
*		@char *original@ = pointer to original base name
*		@char *ext@ = pointer a new extention
*
* Use:		Create name for file
*
*/
char* smart_name ( const char* original, char* ext );


/*unsigned char* smart_name ( char* cp_string, char* ext_string );
*/
/* --- @lba2msf@ --- *
 *
 * Arguments:   @off_t lba@ = logical block addres size
 *              @msf_mode_block *msf_block@ = pointer struct of BCD 
 *
 *
 * Use:         Reads LBA and translate msf.
 */
void lba2msf ( off_t lba, msf_mode_block* msf_block );

/* --- @get_file_size@ --- *
 *
 * Arguments:	@FILE *fptr@ = pointer to FILE
 *
 * Returns:	Size of the file, @-1@ otherwise.
 *
 * Use:		Return the size of the file.
 */
off_t  get_file_size ( FILE* fptr );

/* --- @set_file_pointer@ --- *
 *
 * Arguments:	@FILE *fptr@ = pointer to FILE
 * 		@off_t n_pos@ = the number of bytes to move
 *
 * Returns:	the number of positions the file pointer moved, @-1@ otherwise
 *
 * Use:		Moves the file pointer to the number of position from start.
 */
off_t  set_file_pointer ( FILE* fptr, off_t n_pos );

/* --- @is_svcd_sub_header@ --- *
 *
 * Arguments:	@unsigned char* header@ = the header information
 *
 * Returns:	zero if success, @-1@ otherwise
 *
 * Use:		Write to an iso file.
 */
int is_svcd_sub_header ( unsigned char* header );

/* --- @img_2_img@ --- *
 *
 * Arguments:   @file_ptrs *fptrs@ = input file
 * 		@int block_old@ = size of origin block
 *		@int block_new@ = size of new block
 *		@off_t pregap@ = length of pregap
 *
 *
 * Returns:	mode of image, @-1@ otherwise
 *
 * Use:		convert image to image.  
 */
int img_2_img ( file_ptrs* fptrs,  int block_old, int block_new, off_t pregap );

#ifdef __cplusplus
} 	/* extern "C" */
#endif	/* __cplusplus */

#endif /* UTIL_H */
