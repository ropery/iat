/**
 * Copyright (C) 2009 
 *      - Salvatore Santagati <salvatore.santagati@gmail.com>
 *      - Abdur Rab <c.abdur@yahoo.com>
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

#ifndef DEBUG_H
#define DEBUG_H

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

#ifndef ECMA119_H
#include "ecma119.h"
#endif

typedef struct sub_mode_info {
	int mode;
	int file_number;
	int channel;
	int coding;
	int sub_mode;
	int eof;
	int realtime;
	int trigger;
	int data;
	int audio;
	int video;
	int eor;
} sub_mode_info;


/* --- @display_pvd_info@ --- *
 *
 * Arguments:   @iso_primary_descriptor* pvd@ = primary volume descriptor
 *
 * Returns:     ---

 * Use:         Displays the primary volume description.
 */
void display_pvd_info ( iso_primary_descriptor* pvd );

/* --- @is_same_previous_content@ --- *
 *
 * Arguments:   @sub_mode_info* previous@ = previous block mode information
 *		@sub_mode_info* current@ = current block mode information
 *
 * Returns:     Zeor on success, @-1@ or @1@ on error.

 * Use:         Checks wheather the previous block equals current block.
 */
int is_same_previous_content ( sub_mode_info* previous, sub_mode_info* current );

/* --- @display_sub_mode@ --- *
 *
 * Arguments:   @sub_mode_info* current@ = current block mode information
 *
 * Returns:     ---

 * Use:         Displays the sub mode information.
 */
void display_sub_mode ( sub_mode_info* current );

/* --- @display_mode_info@ --- *
 *
 * Arguments:   @unsigned char* buffer@ = pointer to the buffer
 *              @image_struct *img_struct@ = pointer struct of type image and pregap of image
 *		@sub_mode_info* previous@ = previous block mode information
 *		@long block_number@ = block number from the start
 *		@off_t n_loop@ = number of byte from where the block starts
 *
 * Returns:     Zeor on success, @-1@ on error.

 * Use:         Displays the mode information.
 */
int display_mode_info ( unsigned char* buffer, image_struct*  img_struct, sub_mode_info* previous, long	block_number, off_t n_loop );

/* --- @image_debug@ --- *
 *
 * Arguments:   @file_ptrs *fptrs@ = pointer struct of source and destination file
 *              @image_struct *img_struct@ = pointer struct of type image and pregap of image
 *
 * Returns:     Zeor on success, @-1@ on error.
 *
 * Use:         Return the detection of the image.
 */
int  debug ( file_ptrs* fptrs,  image_struct*  img_struct );

#ifdef __cplusplus
}       /* extern "C" */
#endif  /* __cplusplus */

#endif /* DEBUG_H */

