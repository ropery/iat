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

/* ---@free_allocated_memory@ ---*
*
* Arguments:	@void* pointer_to_free@ = pointer to be freed
*
* Returns:	---
*
* Use:		Frees the allocated memory.
*
*/
void free_allocated_memory ( void* pointer_to_free )
{
	if ( pointer_to_free ) free ( pointer_to_free );
}

/* ---@copy_string@ ---*
*
* Arguments:	@const char* cp_string@ = pointer to string to be copied
*
* Returns:	The copied string if successful, @NULL@ otherwise.
*
* Use:		Copies the string to the newly allocated space.
*
*/
char* copy_string ( const char* cp_string )
{
	char* return_value = NULL;
	size_t length = 0;
	length = ( strlen ( cp_string ) + 1 );
	return_value = ( char* ) malloc ( sizeof ( char ) * length );
	if ( return_value ) {
		memset ( return_value, 0, length );
		memmove ( return_value, cp_string, ( length - 1 ) );
	}
	return ( return_value );
}

/* ---@smart_name@ ---*
*
* Arguments:	@const char *original@ = pointer to original base name
*		@const char *ext@ = pointer a new extention
*
* Returns:	The copied string if successful, @NULL@ otherwise.
*
* Use:		Creates smart name for file
*
*/
char* smart_name ( const char* original, const char* ext )
{
	char* buffer = NULL;
	char* tmp_buffer = NULL;
	size_t length = 0;
	size_t file_ext_lenght = 0;

	if ( ( NULL == original ) || ( NULL == ext ) ) return ( NULL );

	if ( NULL != ( tmp_buffer = strrchr ( original, '.' ) ) ) {
		if ( !memcmp ( ( tmp_buffer + 1 ), ext, strlen ( ext ) ) ) {
			if ( 0 > ( length = tmp_buffer - original ) ) return ( buffer );
			file_ext_lenght += strlen ( ext ); /* to include the extension */
			file_ext_lenght += 4; /* for including '_0.' and 'null' char */

			buffer = ( char* ) malloc ( sizeof ( char ) * ( length + file_ext_lenght ) );
			if ( buffer ) {
				memset ( buffer, 0, ( length + file_ext_lenght ) );
				memmove ( buffer, original, length );
				memmove ( buffer + length , "_0.", 3 );
				memmove ( buffer + ( length + 3 ) , ext, strlen ( ext ) );
			}
		} else {
			if ( 0 > ( length = tmp_buffer - original ) ) return ( buffer );
			file_ext_lenght += strlen ( ext ); /* to include the extension */
			file_ext_lenght += 2; /* for including '.' and 'null' char */

			buffer = ( char* ) malloc ( sizeof ( char ) * ( length + file_ext_lenght ) );
			if ( buffer ) {
				memset ( buffer, 0, ( length + file_ext_lenght ) );
				memmove ( buffer, original, length );
				memmove ( buffer + length , ".", 1 );
				memmove ( buffer + ( length + 1 ) , ext, strlen ( ext ) );
			}
		}
	} else {
		file_ext_lenght += strlen ( ext ); /* to include the extension */
		file_ext_lenght += 2; /* for including '.' and 'null' char */
		length = strlen ( original );

		buffer = ( char* ) malloc ( sizeof ( char ) * ( length + file_ext_lenght ) );
		if ( buffer ) {
			memset ( buffer, 0, ( length + file_ext_lenght ) );
			memmove ( buffer, original, length );
			memmove ( buffer + length , ".", 1 );
			memmove ( buffer + ( length + 1 ) , ext, strlen ( ext ) );
		}
	}

	return ( buffer );

}

/*
unsigned char* smart_name ( char* cp_string, char* ext_string )
{
	unsigned char* return_value = NULL;

	return_value = strtok ( cp_string , "." );

	strncat( return_value, ext_string , ( strlen ( ext_string ) ) );
	printf ( "smart name (%s)\n", return_value );
	return ( return_value );
}
*/
/* --- @lba2msf@ --- *
 *
 * Arguments:   @off_t lba@ = logical block addres size
 *              @msf_mode_block *msf_block@ = pointer struct of BCD
 *
 *
 * Use:         Reads LBA and translate msf.
 */
void lba2msf ( off_t lba, msf_mode_block* msf_block )
{
	(*( msf_block->frame  ) ) = lba % 75;
	(*( msf_block->second ) ) = ( ( lba / 75 ) + 2 ) % 60;
	(*( msf_block->minute ) ) = ( ( lba / 75 ) + 2 ) / 60;
}

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
	fseeko ( fptr, ( off_t ) 0, SEEK_END );
	return ( ftello ( fptr ) );
}

/* --- @set_file_pointer@ --- *
 *
 * Arguments:	@FILE *fptr@ = pointer to FILE
 * 		@off_t n_pos@ = the number of bytes to move
 *
 * Returns:	the number of positions the file pointer moved, @-1@ otherwise
 *
 * Use:		Moves the file pointer to the number of position from start.
 */
off_t  set_file_pointer ( FILE* fptr, off_t n_pos )
{
	if ( get_file_size ( fptr ) < n_pos ) return ( -1 );
	fseeko ( fptr, ( off_t ) 0, SEEK_SET );
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
int img_2_img ( file_ptrs* fptrs,  int block_old, int block_new, off_t pregap )
{
        int	return_value = ERROR;
	char*	fimg =  NULL;
	off_t	n_loop;
	off_t	n_img_size;

	if ( ( n_img_size = get_file_size ( fptrs -> fsource ) ) < 1 ) return ( return_value ); /* The image file is empty */
	if ( NULL == ( fimg = malloc ( sizeof ( char ) * block_old ) ) ) return ( return_value ); /* Could not allocate memory */

	set_file_pointer ( fptrs -> fsource, pregap );

	for ( n_loop = pregap  ; n_loop <  n_img_size ; n_loop += block_old ) {
		progress_bar ( ( ( n_loop + 1 ) * 100 ) / n_img_size );
		memset ( fimg, 0, ( unsigned int ) block_old );
		fread  ( fimg , 1, ( unsigned int ) block_old, fptrs -> fsource );
		fwrite ( fimg, 1, ( unsigned int ) block_new, fptrs -> fdest );
		return_value = AOK;
	}

	set_file_pointer ( fptrs -> fsource, ( off_t ) 0 );
	free_allocated_memory ( ( void* ) fimg );

	progress_bar ( 100 );
	printf ( "\n\n" );

	return ( return_value );
}

