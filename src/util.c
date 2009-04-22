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
#include "util.h"
#endif

/* --- @get_file_size@ --- *
 *
 * Arguments:	@FILE *fptr@ = pointer to FILE
 *
 * Returns:	Size of the file, @-1@ otherwise.
 *
 * Use:		Return the size of the file.
 */
off_t  get_file_size ( FILE* fptr )
{
	if ( NULL == fptr ) return ( -1 );
	fseeko ( fptr, 0L, SEEK_END );
	return ( ftello ( fptr ) );	
}

/* --- @set_file_pointer@ --- *
 *
 * Arguments:	@FILE *fptr@ = pointer to FILE
 * 		@long n_pos@ = the number of bytes to move
 *
 * Returns:	the number of positions the file pointer moved, @-1@ otherwise
 *
 * Use:		Moves the file pointer to the number of position from start.
 */
off_t  set_file_pointer ( FILE* fptr, long n_pos )
{
	if ( get_file_size ( fptr ) < n_pos ) return ( -1 );
	fseeko ( fptr, 0L, SEEK_SET );
	fseeko ( fptr, n_pos, SEEK_CUR );
	return ( n_pos );
}

/* --- @is_svcd_sub_header@ --- *
 *
 * Arguments:	@unsigned char* header@ = the header information
 *
 * Returns:	zero if success, @-1@ otherwise
 *
 * Use:		Write to an iso file.
 */
int is_svcd_sub_header ( unsigned char* header )
{
	/* SVCD SUB HEADER for BLOCK 2336 */
	unsigned const char svcd_header [ 4 ] [ 8 ] = { 
		{ 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x08, 0x00 }, 
		{ 0x00, 0x00, 0x09, 0x00, 0x00, 0x00, 0x09, 0x00 }, 
		{ 0x00, 0x00, 0x88, 0x00, 0x00, 0x00, 0x88, 0x00 }, 
		{ 0x00, 0x00, 0x89, 0x00, 0x00, 0x00, 0x89, 0x00 }		
	};

	int n_count = 0;
	int n_return_value = ERROR;
	for ( n_count = 0; n_count < 4; n_count++ ) {
		if ( ( !memcmp ( header, svcd_header [ n_count ], 8 ) ) ) {
			n_return_value = AOK;
			break;
		}
	}

	return ( n_return_value );
}

