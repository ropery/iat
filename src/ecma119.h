/**
 * Copyright (C) 2008 
 *	- Salvatore Santagati <salvatore.santagati@gmail.com>
 * Copyright (C) 2009
 * 	- Salvatore Santagati  <salvatore.santagati@gmail.com>
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

#ifndef ECMA119_H
#define ECMA119_H

#ifdef __cplusplus
extern "C" {
#endif  /* __cplusplus */

typedef unsigned char		iso711_t;
typedef	signed	 char		iso712_t;	
typedef unsigned short		iso721_t; 
typedef unsigned short		iso722_t;
typedef unsigned long		iso723_t; 
typedef unsigned long 		iso731_t;  
typedef unsigned long 	   	iso732_t; 
typedef unsigned long long 	iso733_t; 

#define ISODCL(from, to) (to - from + 1)

typedef char     achar_t;  
typedef char     dchar_t;

#define ISO_STANDARD_ID      "CD001"  	

#define ISO_VD_TYPE_BOOT_RECORD		0
#define ISO_VD_TYPE_PRIMARY		1
#define ISO_VD_TYPE_SUPPLEMENTARY	2
#define ISO_VD_TYPE_PARTITION		3
#define ISO_VD_TYPE_SET_TERMINATOR	255

typedef struct iso_vd_format {
 iso711_t	type	[ISODCL(1,	   1)];
 char		id	[ISODCL(2,	   6)];
 iso711_t	version [ISODCL(7,	   7)];
 char		vd_type [ISODCL(8,	2048)];
} iso_vd_format;

struct iso_vd_boot_record {
 iso711_t		type					[ISODCL(1,	   1)];
 char			id					[ISODCL(2,	   6)];	 	
 iso711_t	 	version					[ISODCL(7,	   7)];
 achar_t		boot_system_id				[ISODCL(8,	  39)];
 achar_t		boot_id					[ISODCL(40,	  71)];
 char			boot_system_use				[ISODCL(72,	2048)];
};

struct iso_vd_set_terminator {
 iso711_t		type					[ISODCL(1,	   1)];
 char			id					[ISODCL(2,	   6)];
 iso711_t		version					[ISODCL(7,	   7)];
 char			reserved				[ISODCL(8,	2048)];
};

typedef struct iso_primary_descriptor {
        iso711_t type                   [ISODCL(1,    1)]; /* 711 */
        char id                         [ISODCL(2,    6)];
        iso711_t version                [ISODCL(7,    7)]; /* 711 */
        char unused                     [ISODCL(8,    8)];
        achar_t system_id               [ISODCL(9,   40)]; /* achars */
        dchar_t volume_id               [ISODCL(41,  72)]; /* dchars */
        char unused2                    [ISODCL(73,  80)];
        char volume_space_size          [ISODCL(81,  88)]; /* 733 */
        char escape_sequences           [ISODCL(89, 120)];
        char volume_set_size            [ISODCL(121, 124)]; /* 723 */
        char volume_sequence_number     [ISODCL(125, 128)]; /* 723 */
        char logical_block_size         [ISODCL(129, 132)]; /* 723 */
        char path_table_size            [ISODCL(133, 140)]; /* 733 */
        char type_l_path_table          [ISODCL(141, 144)]; /* 731 */
        char opt_type_l_path_table      [ISODCL(145, 148)]; /* 731 */
        char type_m_path_table          [ISODCL(149, 152)]; /* 732 */
        char opt_type_m_path_table      [ISODCL(153, 156)]; /* 732 */
        char root_directory_record      [ISODCL(157, 190)]; /* 9.1 */
        char volume_set_id              [ISODCL(191, 318)]; /* dchars */
        char publisher_id               [ISODCL(319, 446)]; /* achars */
        char data_preparer_id           [ISODCL(447, 574)]; /* achars */
        char application_id             [ISODCL(575, 702)]; /* achars */
        char copyright_file_id          [ISODCL(703, 739)]; /* 7.5 dchars */
        char abstract_file_id           [ISODCL(740, 776)]; /* 7.5 dchars */
        char bibliographic_file_id      [ISODCL(777, 813)]; /* 7.5 dchars */
        char creation_date_and_time     [ISODCL(814, 830)]; /* 8.4.26.1 */
        char modification_date_and_time [ISODCL(831, 847)]; /* 8.4.26.1 */
        char expiration_date_and_time   [ISODCL(848, 864)]; /* 8.4.26.1 */
        char effective_date_and_time    [ISODCL(865, 881)]; /* 8.4.26.1 */
        char file_structure_version     [ISODCL(882, 882)]; /* 711 */
        char reserved                   [ISODCL(883, 883)];
        char application_use            [ISODCL(884, 1395)];
        char reserved2                  [ISODCL(1396, 2048)];
} iso_primary_descriptor;


typedef struct iso_vd_primary {
 iso711_t		type					[ISODCL(1,	 1)];
 char 			id					[ISODCL(2,	 6)];
 iso711_t		version					[ISODCL(7,	 7)];
 char			unused					[ISODCL(8,	 8)];
 achar_t 		system_id				[ISODCL(9,	 40)];
 dchar_t 		volume_id				[ISODCL(41,	 72)];
 char			unused2					[ISODCL(73,	 80)];
 iso733_t		volume_space_size			[ISODCL(81,	 88)];
 char			unused3					[ISODCL(89,	 120)];
 iso723_t		volume_set_size	;		/*	[ISODCL(121,	 124)];*/ 
 iso723_t		volume_sequence_number;		/*      [ISODCL(125,	 128)];*/
 iso723_t		logical_block_size;		/*	[ISODCL(129,	 132)];*/
 iso733_t		path_table_size;		/*	[ISODCL(133,	 140)];*/			
 iso731_t		type_l_path_table;		/*	[ISODCL(141,	 144)];*/
 iso731_t 		optional_type_l_path_table;	/*	[ISODCL(145,	 148)];*/
 iso732_t		type_m_path_table;		/*	[ISODCL(149,	 152)];*/
 iso732_t		optional_type_m_path_table;	/*	[ISODCL(153,	 156)];*/	
 char 			directory_record_for_root_directory	[ISODCL(157,	 190)];	
 dchar_t		volume_set_id				[ISODCL(191,	 318)];
 achar_t		publisher_id				[ISODCL(319,	 446)];
 achar_t		data_preparer_id			[ISODCL(447,	 574)];	
 achar_t		application_id				[ISODCL(575,	 702)];
 char			copyright_file_id			[ISODCL(703,	 739)];
 char			abstract_file_id			[ISODCL(740,	 776)];
 char			bibliographic_file_id			[ISODCL(777,	 813)];
 char			creation_date_and_time			[ISODCL(814,	 830)];
 char			modification_date_and_time		[ISODCL(831,	 847)];
 char			expiration_date_and_time		[ISODCL(848,	 864)];
 char			effective_date_and_time			[ISODCL(865,	 881)];
 iso711_t		file_structure_version			[ISODCL(882,	 882)];
 char			reserved				[ISODCL(883,	 883)];			
 char			aplication_use				[ISODCL(884,	1395)];				
 char			reserved2				[ISODCL(1396,	2048)];
} iso_vd_primary;

struct iso_vd_supplementary {
 iso711_t		type					[ISODCL(1,	 1)];
 char 			id					[ISODCL(2,	 6)];
 iso711_t		version					[ISODCL(7,	 7)];
 char			flag					[ISODCL(8,	 8)];
 achar_t 		system_id				[ISODCL(9,	 40)];
 dchar_t 		volume_id				[ISODCL(41,	 72)];
 char			unused1					[ISODCL(73,	 80)];
 iso733_t		volume_space_size			[ISODCL(81,	 88)];
 char			escape					[ISODCL(89,	 120)];
 iso723_t		volume_set_size	;		/*	[ISODCL(121,	 124)];*/ 
 iso723_t		volume_sequence_number;		/*      [ISODCL(125,	 128)];*/
 iso723_t		logical_block_size;		/*	[ISODCL(129,	 132)];*/
 iso733_t		path_table_size;		/*	[ISODCL(133,	 140)];*/			
 iso731_t		type_l_path_table;		/*	[ISODCL(141,	 144)];*/
 iso731_t 		optional_type_l_path_table;	/*	[ISODCL(145,	 148)];*/
 iso732_t		type_m_path_table;		/*	[ISODCL(149,	 152)];*/
 iso732_t		optional_type_m_path_table;	/*	[ISODCL(153,	 156)];*/	
 char 			directory_record_for_root_directory	[ISODCL(157,	 190)];	
 dchar_t		volume_set_id				[ISODCL(191,	 318)];
 achar_t		publisher_id				[ISODCL(319,	 446)];
 achar_t		data_preparer_id			[ISODCL(447,	 574)];	
 achar_t		application_id				[ISODCL(575,	 702)];
 char			copyright_file_id			[ISODCL(703,	 739)];
 char			abstract_file_id			[ISODCL(740,	 776)];
 char			bibliographic_file_id			[ISODCL(777,	 813)];
 char			creation_date_and_time			[ISODCL(814,	 830)];
 char			modification_date_and_time		[ISODCL(831,	 847)];
 char			expiration_date_and_time		[ISODCL(848,	 864)];
 char			effective_date_and_time			[ISODCL(865,	 881)];
 iso711_t		file_structure_version			[ISODCL(882,	 882)];
 char			reserved				[ISODCL(883,	 883)];			
 char			aplication_use				[ISODCL(884,	1395)];				
 char			reserved2				[ISODCL(1396,	2048)];
};		

struct iso_vd_partition {
 iso711_t		type					[ISODCL(1,	   1)];
 char 			id					[ISODCL(2,	   6)];
 iso711_t		version					[ISODCL(7,	   7)];
 char			unused					[ISODCL(8,	   8)];
 achar_t 		system_id				[ISODCL(9,	  40)];
 dchar_t 		volume_partition_id			[ISODCL(41,	  72)];
 iso733_t		volume_partition_location;  /*		[ISODCL(73,	  80)];*/
 iso733_t		volume_partition_size;	   /*		[ISODCL(81,	  88)];*/
 char			system_use				[ISODCL(89,	2048)]; 
}; 
		
struct iso_date_and_time_format {
 char		year		[ISODCL(1,   4)];
 char		month		[ISODCL(5,   6)];
 char		day		[ISODCL(7,   8)];
 char		hour		[ISODCL(9,  10)];
 char		minute		[ISODCL(11, 12)];
 char		second		[ISODCL(13, 14)];
 char		hundredth 	[ISODCL(15, 16)];
 iso712_t	greenwich	[ISODCL(17, 17)];
};

struct iso_file_and_directory {
 iso711_t	len_dr 		[ISODCL(1,  1)];
 iso711_t	ext_len_dr	[ISODCL(2,  2)];
 iso733_t	location_ext;/*	[ISODCL(3, 10)]; */
 iso733_t	data_leght;  /*	[ISODCL(11,18)];*/ 
 iso711_t	rec_date_time	[ISODCL(19,25)];
 char		flags		[ISODCL(26,26)];
 iso711_t	unit_size	[ISODCL(27,27)];
 iso711_t	gap_size	[ISODCL(28,28)];
 iso723_t	vol_seq_num; /* [ISODCL(29,32)];*/
 iso711_t	len_fi		[ISODCL(33,33)];
 char		name	[34];
};

struct iso_date_and_time_recording {
 char	year 		[ISODCL(1,1)];
 char	month		[ISODCL(2,2)];
 char	day		[ISODCL(3,3)];
 char	hour		[ISODCL(4,4)];
 char	minute		[ISODCL(5,5)];
 char	second		[ISODCL(6,6)];
 char	greenwich 	[ISODCL(7,7)];
};

#define ISO_FILE_EXISTENCE 	1
#define ISO_FILE_DIRECTORY 	2
#define ISO_FILE_ASSOCIATED 	4
#define ISO_FILE_RECORD		8
#define ISO_FILE_PROTECTION	16
#define ISO_FILE_RESERVED1	32
#define ISO_FILE_RESERVED2	64
#define ISO_FILE_MULTIEXTENT	128
 

struct iso_path_table_record {
 iso711_t	len_di				[ISODCL(1,1)];
 iso711_t	ext_attribute_record_len	[ISODCL(2,2)];
 char		location_ext			[ISODCL(3,6)];
 char		parent_dir_num			[ISODCL(7,8)];
 char		name[1];  
};

struct iso_ext_attr_record {
 iso723_t	owner;		/*		[ISODCL(1,	 4)];*/
 iso723_t 	group;		/*		[ISODCL(5,	 8)];*/
 char		permissions			[ISODCL(9,	10)];
 char		creation_date			[ISODCL(11,	27)];
 char 		modification_date		[ISODCL(28,	44)];
 char 		expiration_date			[ISODCL(45,	61)];
 char 		effective_date			[ISODCL(62,	78)];
 iso711_t	record_format			[ISODCL(79,	79)];
 iso711_t	record_attributes		[ISODCL(80,	80)];
 iso723_t	record_length;  /*		[ISODCL(81,	84)];*/
 char		sytem_id			[ISODCL(85,	116)];
 char		system_use			[ISODCL(117,	180)];
 iso711_t	ext_attr_record_version		[ISODCL(181, 	181)];
 iso711_t	len_esc				[ISODCL(182,	182)];
 char		reserved1			[ISODCL(183,	246)];
 iso723_t	len_au;		/*		[ISODCL(247,	250)];*/
 char		application_use		[1];
};

/* File permissions */

#define ISO_GROUP_SYSTEM_READ		0x0001
#define ISO_BIT_1			0x0002
#define ISO_GROUP_SYSTEM_EXECUTE	0x0004
#define ISO_BIT_3			0x0008

#define ISO_OWNER_READ			0x0010
#define ISO_BIT_5			0x0020
#define ISO_OWNER_EXECUTE		0x0040
#define ISO_BIT_7			0x0080

#define ISO_GROUP_READ			0x0100
#define ISO_BIT_9			0x0200
#define ISO_GROUP_EXECUTE		0x0400
#define ISO_BIT_11			0x0800

#define ISO_OTHER_READ			0x1000
#define ISO_BIT_13			0x2000
#define ISO_OTHER_EXECUTE		0x4000
#define ISO_BIT_15			0x8000

/* Record Format */

#define ISO_RF_NOT_SPECIFIED 		0
#define ISO_RF_FIXED_LENGHT		1
#define ISO_RF_VARIABLE_LENGHT_RCW_721	2
#define ISO_RF_VARIABLE_LENGHT_RCW_722	3

/* Record Attributes */

#define ISO_RA_LF_CR	0
#define ISO_RA_VS	1
#define ISO_RA_NCF	2

/* Record Lenght */

#define ISO_RL_0	0
#define ISO_RL_BYTES	1
#define ISO_RL_MAX_2	2
#define ISO_RL_MAX_3	3

#ifdef __cplusplus
}       /* extern "C" */
#endif  /* __cplusplus */

#endif /* ECMA119 */ 
