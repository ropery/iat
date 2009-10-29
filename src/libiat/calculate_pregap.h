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
#define CALCULATE_PREGAP_H

#include <string.h>

#ifndef DEFINE_H
#include "define.h"
#endif

#ifndef UTIL_H
#include "util.h"
#endif

#ifdef __cplusplus
extern "C" {
#endif	/* __cplusplus */

/* --- @is_udf_image@ --- *
 *
 * Arguments:   @unsigned char* header@ = the header information
 *
 * Returns:     zero if success, @-1@ otherwise
 *
 * Use:         Return the detection of the header.
 */
int is_udf_image  ( unsigned char* header );

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
off_t calculate_pregap_length ( off_t  cd_id_start, image_struct* img_struct, int header );

/* --- @calculate_block_size@ --- *
 *
 * Arguments:	@off_t cd_id_start@ = bytes when is detect primary volume of CD/DVD 
 *		@off_t cd_id_end@	= bytes when is present next volume of CD/DVD
 * 
 * Returns :	block size.
 * 
 * Use:		Return block size image.
 */
size_t calculate_block_size ( off_t cd_id_start, off_t cd_id_end, image_struct* img_struct );

/* --- @calculate_pregap@ --- *
 *
 * Arguments:   @file_ptrs *fptrs@ = pointer struct of source and destination file
 *		@image_struct *img_struct@ = pointer struct of type image and pregap of image
 *
 * Returns:     Zeor on success, @-1@ on error.
 *
 * Use:         Return the detection of the image.
 */
off_t calculate_pregap ( file_ptrs* fptrs,  image_struct*  img_struct );

#ifdef __cplusplus
}	/* extern "C" */
#endif	/* __cplusplus */

#endif /* CALCULATE_PREGAP_H */
