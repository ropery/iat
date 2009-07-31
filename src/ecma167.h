/**
 * Copyright (C) 2009
 *	- Salvatore Santagati <salvatore.santagati@gmail.com>
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

#ifndef ECMA167_H
#define ECMA167_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif  /* __cplusplus */

#ifndef DEFINE_H
#include "define.h"
#endif

#define TAG_IDENT_PVD			0x0001
#define TAG_IDENT_AVDP			0x0002
#define UDF_BLOCKSIZE			2048

/* Descriptor Tag (ECMA 167r3 3/7.2) */
typedef struct udf_tag {
	uint16_t	tag_id;
	uint16_t	tag_desc_version;
	uint8_t		tag_cksum;
	uint8_t		tag_reserved;
	uint16_t	tag_serial_num;
	uint16_t	tag_desc_CRC;
	uint16_t	tag_desc_CRC_len;
	uint32_t	tag_loc;
} udf_tag;

/* Extent Descriptor (ECMA 167r3 3/7.1) */
typedef struct udf_extent_ad {
	uint32_t	len;
	uint32_t	loc;
} udf_extent_ad;

/* Anchor Volume Descriptor Pointer (ECMA 167r3 3/10.2) */
typedef struct udf_anchor_volume_descriptor {
	udf_tag		desc_tag;
	udf_extent_ad	main_vol_desc_seq_ext;
	udf_extent_ad	reserve_vol_desc_seq_ext;
	uint8_t		reserved [480];
} udf_anchor_volume_descriptor;

/* Character set specification (ECMA 167r3 1/7.2.1) */
typedef struct udf_charspec {
	uint8_t		char_set_type;
	uint8_t		char_set_info [ 63 ];
} udf_charspec;

/* Timestamp (ECMA 167r3 1/7.3) */
typedef struct udf_timestamp {
	uint16_t	type_and_timezone;
	uint16_t	year;
	uint8_t		month;
	uint8_t		day;
	uint8_t		hour;
	uint8_t		minute;
	uint8_t		second;
	uint8_t		centiseconds;
	uint8_t		hundreds_of_microseconds;
	uint8_t		microseconds;
} udf_timestamp;

/* Entity identifier (ECMA 167r3 1/7.4) */
typedef struct udf_regid {
	uint8_t		flags;
	uint8_t		ident [ 23 ];
	uint8_t		ident_suffix [ 8 ];
} udf_regid;

/* Primary Volume Descriptor (ECMA 167r3 3/10.1) */
typedef struct udf_primary_volume_descriptor {
	udf_tag		desc_tag;
	uint32_t	volume_description_sequence_number;
	uint32_t	primary_volume_description_number;
	uint8_t		volume_id [ 32 ];
	uint16_t	volume_sequence_number;
	uint16_t	max_volume_sequence_number;
	uint16_t	interchange_levle;
	uint16_t	max_interchange_levle;
	uint32_t	char_set_list;
	uint32_t	max_char_set_list;
	uint8_t		volume_set_id [ 128 ];
	udf_charspec	desc_char_set;
	udf_charspec	explanatory_char_set;
	udf_extent_ad	vol_abstract;
	udf_extent_ad	vol_copyright;
	udf_regid	application_id;
	udf_timestamp	creation_date_and_time;
	udf_regid	imp_id;
	uint8_t		application_use [ 64 ];
	uint32_t	predecessor_vol_desc_seq_location;
	uint16_t	flags;
	uint8_t		reserved [ 22 ];
} udf_primary_volume_descriptor;

#ifdef __cplusplus
}       /* extern "C" */
#endif  /* __cplusplus */

#endif /* ECMA167 */
