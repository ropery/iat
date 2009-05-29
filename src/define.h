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

#ifndef DEFINE_H
#define DEFINE_H

#include <stdio.h>

#ifndef CMDLINE_H
#include "cmdline.h"
#endif

#ifdef __cplusplus
extern "C" {
#endif	/* __cplusplus */

typedef struct file_ptrs {
	FILE* fsource;
	FILE* fdesc;
	FILE* fdest;
} file_ptrs;

typedef struct image_struct {
	int	pregap;
	int 	type;
	size_t 	block;
} image_struct;

typedef struct gengetopt_args_info iat_parser;

enum { ERROR = -1, AOK = 0 };

#define IMG_UNKOWN	-1	/* Unkown Image */
#define IMG_AUDIO	1	/* Maybe Audio (only synch byte detect)*/
#define IMG_ISO		2	/* ISO9660 Image (only data id detect)*/
#define IMG_RAW		3	/* Raw Data Image (data id detect + synch)*/
#define IMG_VCD		7	/* VCD or  SVCD (detect VCD/SVCD id) */

#ifdef __cplusplus
}	/* extern "C" */
#endif	/* __cplusplus */

#endif	/* DEFINE_H */

