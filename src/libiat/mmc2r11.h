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

#ifndef MMC2R11_H
#define MMC2R11_H

#ifdef __cplusplus
extern "C" {
#endif	/* __cplusplus */

#define MMCLEN(offset, lenght) (lenght)
#define MMCBYTE(from, to) (to - from + 1)

#define MODE_DATA_0 	0x0000
#define MODE_DATA_1 	0x0001
#define MODE_DATA_2 	0x0002
#define	MODE_RESERVED	0x0003

#define MODE_USER_DATA		0x0000
#define MODE_FOURTH_RUN		0x0020
#define	MODE_THIRD_RUN		0x0040
#define MODE_SECOND_RUN		0x0060
#define MODE_FIRST_RUN		0x0080
#define MODE_LINK_BLOCK		0x00A0
#define MODE_SECOND_RUN_OUT	0x00C0
#define MODE_FIRST_RUN_OUT	0x00E0

typedef struct msf_mode_block {
	unsigned char minute		[ MMCBYTE ( 0, 0 ) ];
	unsigned char second		[ MMCBYTE ( 1, 1 ) ];
	unsigned char frame		[ MMCBYTE ( 2, 2 ) ];
	unsigned char mode		[ MMCBYTE ( 3, 3 ) ];
} msf_mode_block;

typedef struct sync_header_block {
	unsigned char sync_header	[ MMCLEN ( 0, 12 ) ];
	msf_mode_block			msf_block;
} sync_header_block;

typedef struct copy_sub_header {
	unsigned char file		[ MMCBYTE ( 0, 0 ) ];
	unsigned char channel		[ MMCBYTE ( 1, 1 ) ];
	unsigned char sub_mode		[ MMCBYTE ( 2, 2 ) ];
	unsigned char coding		[ MMCBYTE ( 3, 3 ) ];
} copy_sub_header; 

#define SUB_MODE_EOF		0x80
#define SUB_MODE_RT		0x40
#define SUB_MODE_FORM2		0x20
#define SUB_MODE_TRIGGER	0x10
#define SUB_MODE_DATA		0x08
#define SUB_MODE_AUDIO		0x04
#define SUB_MODE_VIDEO		0x02	
#define SUB_MODE_EOR		0x01


typedef struct sub_header_block {
	unsigned char first_copy 	[ MMCLEN ( 0, 4 ) ];	
	unsigned char second_copy   	[ MMCLEN ( 4, 4 ) ];
} sub_header_block;

typedef struct parity_symbol_block {
	unsigned char p_parity		[ MMCLEN ( 0, 172 ) ];
	unsigned char q_parity		[ MMCLEN ( 0, 104 ) ];
} parity_symbol_block;

typedef struct crc_correction_block {
	unsigned char crc		[ MMCLEN ( 0, 4 ) ];
} crc_correction_block;

/* Mode zero (or) Mode 2 Formless */
typedef struct mode_generic {
	sync_header_block		header_block;
	unsigned char user_data		[ MMCLEN ( 16, 2336 ) ];
} mode_generic;

typedef struct mode_one {
	sync_header_block		header_block;
	unsigned char user_data		[ MMCLEN ( 16,	2048 ) ];
	crc_correction_block		crc_block;
	sub_header_block		sub_header;
	parity_symbol_block		parity_block;
} mode_one;

typedef struct mode_two_form_1 {
	sync_header_block		header_block;
	sub_header_block		sub_header;	
	unsigned char user_data		[ MMCLEN ( 24,	2048 ) ];
	crc_correction_block		crc_block;
	parity_symbol_block		parity_block;
} mode_two_form_1;

typedef struct mode_two_form_2 {
	sync_header_block		header_block;
	sub_header_block		sub_header;
	unsigned char user_data		[ MMCLEN ( 24,	2324 ) ];
	crc_correction_block		crc_block;
} mode_two_form_2;

/* Mode two without header */
typedef struct mode_two_form_1_headerless {
	sub_header_block		sub_header;
	unsigned char user_data		[ MMCLEN ( 8, 2048 ) ];
	crc_correction_block		crc_block;
	parity_symbol_block		parity_block;
} mode_two_form_1_headerless;

/* Mode two without header */
typedef struct mode_two_form_2_headerless {
	sub_header_block		sub_header;
	unsigned char user_data		[ MMCLEN ( 8, 2324 ) ];
	crc_correction_block		crc_block;
} mode_two_form_2_headerless;

#ifdef __cplusplus
}	/* extern "C" */
#endif	/* __cplusplus */

#endif	/* MMC2R11_H */
