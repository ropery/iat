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
#define CONVERT_2_ISO_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef __cplusplus
extern "C" {
#endif	/* __cplusplus */

#ifndef DEFINE_H
#include "define.h"
#endif

#ifndef UTIL_H
#include "util.h"
#endif

#ifndef MMC2R11_H
#include "mmc2r11.h"
#endif

#define ISO_PVD_BLOCK 18 /* ISO BLOCK Start and Block End included */

/* --- @mode_0@ --- *
 *
 * Arguments:	@file_ptrs *fptrs@ = pointer struct of source and destination file
 * 		@off_t n_fptr_pos@ = the position of byte from where to be read
 * 		@off_t n_iso_block_no@ = the current block number being written
 *
 * Returns:	the number of bytes read, @-1@ otherwise
 *
 * Use:		Reads into the buffer and writes the buffer to destination file.
 */
off_t mode_0 ( file_ptrs* fptrs, off_t n_fptr_pos, off_t n_iso_block_no );

/* --- @mode_1@ --- *
 *
 * Arguments:	@file_ptrs *fptrs@ = pointer struct of source and destination file
 * 		@off_t n_fptr_pos@ = the position of byte from where to be read
 * 		@off_t n_iso_block_no@ = the current block number being written
 *
 * Returns:	the number of bytes read, @-1@ otherwise
 *
 * Use:		Reads into the buffer and writes the buffer to destination file.
 */
off_t mode_1 ( file_ptrs* fptrs, off_t n_fptr_pos, off_t n_iso_block_no );

/* --- @mode_2_form_1@ --- *
 *
 * Arguments:	@file_ptrs *fptrs@ = pointer struct of source and destination file
 * 		@off_t n_fptr_pos@ = the position of byte from where to be read
 * 		@off_t n_iso_block_no@ = the current block number being written
 *
 * Returns:	the number of bytes read, @-1@ otherwise
 *
 * Use:		Reads into the buffer and writes the buffer to destination file.
 */
off_t mode_2_form_1 ( file_ptrs* fptrs, off_t n_fptr_pos, off_t n_iso_block_no );

/* --- @mode_2_form_2@ --- *
 *
 * Arguments:	@file_ptrs *fptrs@ = pointer struct of source and destination file
 * 		@off_t n_fptr_pos@ = the position of byte from where to be read
 * 		@off_t n_iso_block_no@ = the current block number being written
 *
 * Returns:	the number of bytes read, @-1@ otherwise
 *
 * Use:		Reads into the buffer and writes the buffer to destination file.
 */
off_t mode_2_form_2 ( file_ptrs* fptrs, off_t n_fptr_pos, off_t n_iso_block_no );

/* --- @mode_2@ --- *
 *
 * Arguments:	@file_ptrs *fptrs@ = pointer struct of source and destination file
 * 		@off_t n_fptr_pos@ = the position of byte from where to be read
 * 		@off_t n_iso_block_no@ = the current block number being written
 *
 * Returns:	the number of bytes read, @-1@ otherwise
 *
 * Use:		Reads into the buffer and writes the buffer to destination file.
 */
off_t mode_2 ( file_ptrs* fptrs, off_t n_fptr_pos, off_t n_iso_block_no );

/* --- @mode_2_form_1_headerless@ --- *
 *
 * Arguments:	@file_ptrs *fptrs@ = pointer struct of source and destination file
 * 		@off_t n_fptr_pos@ = the position of byte from where to be read
 * 		@off_t n_iso_block_no@ = the current block number being written
 *
 * Returns:	the number of bytes read, @-1@ otherwise
 *
 * Use:		Reads into the buffer and writes the buffer to destination file.
 */
off_t mode_2_form_2_headerless ( file_ptrs* fptrs, off_t n_fptr_pos, off_t n_iso_block_no );

/* --- @mode_2_form_2_headerless@ --- *
 *
 * Arguments:	@file_ptrs *fptrs@ = pointer struct of source and destination file
 * 		@off_t n_fptr_pos@ = the position of byte from where to be read
 * 		@off_t n_iso_block_no@ = the current block number being written
 *
 * Returns:	the number of bytes read, @-1@ otherwise
 *
 * Use:		Reads into the buffer and writes the buffer to destination file.
 */
off_t mode_2_form_2_headerless ( file_ptrs* fptrs, off_t n_fptr_pos, off_t n_iso_block_no );

/* --- @bin_2_iso@ --- *
 *
 * Arguments:	@file_ptrs *fptrs@ = pointer struct of source and destination file
 * 		@image_struct *img_struct@ = struct of image pregap
 *
 * Returns:	Zeor on success, @-1@ on error.
 *
 * Use:		Return the detection of the image.
 */
int bin_2_iso ( file_ptrs* fptrs,  image_struct*  img_struct );

/* --- @img_2_iso@ --- *
 *
 * Arguments:   @file_ptrs *fptrs@ = pointer struct of source and destination file
 *              @image_struct *img_struct@ = struct of image pregap
 *
 * Returns:     Zeor on success, @-1@ on error.
 *
 * Use:         Return the detection of the image.
 */
int img_2_iso ( file_ptrs* fptrs,  image_struct*  img_struct );

#ifdef __cplusplus
} 	/* extern "C" */
#endif	/* __cplusplus */

#endif /* CONVERT_2_ISO_H */

