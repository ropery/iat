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

#ifndef DEBUG_H
#include "debug.h"
#endif

/* --- @print_udf@ --- *
 *
 * Temporary function, will be removed in the release
 */
void print_udf ( unsigned char* ptr, int n_len ) 
{
	int n_loop = 0;
	if ( n_len > 0 ) {
		/*printf( "(" );*/
		for ( n_loop = 0; n_loop < n_len; n_loop++ ) {
			printf ("%c", (unsigned char) *( ptr + n_loop ) );
		}
		/*printf( ")" );*/
	}
}

/* --- @print_udf@ --- *
 *
 * Temporary function, will be removed in the release
 */
void print_signed_char ( char* ptr, int n_len ) 
{
	int n_loop = 0;
	if ( n_len > 0 ) {
		/*printf( "(" );*/
		for ( n_loop = 0; n_loop < n_len; n_loop++ ) {
			printf ( "%c", (char) *( ptr + n_loop ) );
		}
		/*printf( ")" );*/
	}
}

/* --- @print_udf@ --- *
 *
 * Temporary function, will be removed in the release
 */
void print_hex ( unsigned char* ptr, int n_len ) 
{
	int n_loop = 0;
	if ( n_len > 0 ) {
		/*printf( "(" );*/
		for ( n_loop = 0; n_loop < n_len; n_loop++ ) {
			printf ( "%2x\t", *( ptr + n_loop ) );
		}
		/*printf( ")" );*/
	}
}

int isonum_721 ( char* p )
{
        return ( ( p[0] & 0xff ) | ( ( p[1] & 0xff ) << 8 ) );
}

int isonum_723 ( char* p )
{
        if ( p[0] != p[3] || p[1] != p[2] ) {
		fprintf ( stderr, "invalid format 7.2.3 number\n" );
		return ( -1 );
        }

        return ( isonum_721 ( p ) );
}

int isonum_731 ( char* p )
{
        return ( 
		( p [ 0 ] & 0xff ) 
                | ( ( p [ 1 ] & 0xff ) << 8 )
                | ( ( p [ 2 ] & 0xff ) << 16 )
                | ( ( p [ 3 ] & 0xff ) << 24 ) 
		);
}

int isonum_732 ( char* p )
{
        return ( 
		( p [ 3 ] & 0xff )
                | ( ( p [ 2 ] & 0xff ) << 8 )
                | ( ( p [ 1 ] & 0xff ) << 16 )
                | ( ( p [ 0 ] & 0xff ) << 24 )
		);
}

int isonum_733 ( char* p )
{
        return ( isonum_731 ( ( char* ) p ) );
}

/* --- @display_pvd_info@ --- *
 *
 * Arguments:   @iso_primary_descriptor* pvd@ = primary volume descriptor
 *
 * Returns:     ---

 * Use:         Displays the primary volume description.
 */
void display_pvd_info ( iso_primary_descriptor* pvd )
{
	/* PVD IS ON  LBA 16 */ 
	/* ECMA 119 - 8.4 Primary Volume Descriptor*/
	int nvalue = 0;
	printf ( "TYPE\t	: (%d)\n", ( *( pvd -> type ) ) );
	printf ( "ID\t	: " ); print_signed_char ( ( pvd -> id ), 5 ); printf ( "\n" );
	printf ( "VERSION\t	: (%d)\n", ( *( pvd -> version ) ) );
	printf ( "SYSTEM ID\t: " ); print_signed_char ( ( pvd -> system_id ), 32 ); printf ( "\n" );
	printf ( "VOLUME ID\t: " ); print_signed_char ( ( pvd -> volume_id ), 32 ); printf ( "\n" );
	printf ( "VOLUME SPACE\t: %ld\n", isonum_733 ( pvd -> volume_space_size ) );
	printf ( "VOLUME SET\t: %d\n", isonum_723 ( pvd -> volume_set_size ) ); 
	printf ( "VOLUME NUMBER\t: %d\n", isonum_723 ( pvd -> volume_sequence_number ) );
	printf ( "LOGICAL BLOCK\t: %d\n", isonum_723 ( pvd -> logical_block_size ) );
	printf ( "PATH TABLE\t: %ld\n", isonum_733 ( pvd -> path_table_size ) );
	printf ( "PATH TABLE L\t: %ld\n", isonum_731 ( pvd -> type_l_path_table ) );
	printf ( "TYPE TABLE L\t: %ld\n", isonum_731 ( pvd -> opt_type_l_path_table ) );
	printf ( "PATH TABLE M\t: %ld\n", isonum_732 ( pvd -> type_m_path_table ) );
	printf ( "TYPE TABLE M\t: %ld\n", isonum_732 ( pvd -> opt_type_m_path_table ) );
	printf ( "ROOT DIR\t: %ld\n", ( *( pvd ->  root_directory_record  ) ) );
	printf ( "VOLUME SET ID\t: " ); print_signed_char ( ( pvd -> volume_set_id), 128 ) ; printf ( "\n" );/* right ?!?!? */ 
	printf ( "PUBLISHER\t: " ); print_signed_char ( ( pvd -> publisher_id ), 128 );  printf ( "\n" );
	printf ( "PREPARED\t: " ); print_signed_char ( ( pvd -> data_preparer_id ), 32 ); printf ( "\n" );
	printf ( "APPLICATION\t: " ); print_signed_char ( ( pvd -> application_id ), 128 );  printf ( "\n" );
	printf ( "COPYRIGHT\t: " ); print_signed_char ( ( pvd -> copyright_file_id ), 37 ); printf ( "\n" );
	printf ( "ABSTRACT\t: " ); print_signed_char ( ( pvd -> abstract_file_id ), 37 ); printf ( "\n" );
	printf ( "CREATED\t	: " ); print_signed_char ( ( pvd -> creation_date_and_time ), 17 ); printf ( "\n" );
	printf ( "MODIFICATED\t: " ); print_signed_char ( ( pvd -> modification_date_and_time ), 17 ); printf ( "\n" );
	printf ( "EXPIRE\t	: " ); print_signed_char ( ( pvd -> expiration_date_and_time ), 17 ); printf ( "\n" );
	printf ( "DATA\t	: " ); print_signed_char ( ( pvd -> effective_date_and_time ), 17 ); printf ( "\n" );
	printf ( "FILE VERSION\t: %d\n",  ( *( pvd -> file_structure_version ) ) ); 
	printf ( "APPLICATION USE\t: " ); print_signed_char ( ( pvd -> application_use ), 512 ); printf ( "\n" ); 
}

/* --- @is_same_previous_content@ --- *
 *
 * Arguments:   @sub_mode_info* previous@ = previous block mode information
 *		@sub_mode_info* current@ = current block mode information
 *
 * Returns:     Zeor on success, @-1@ or @1@ on error.

 * Use:         Checks wheather the previous block equals current block.
 */
int is_same_previous_content ( sub_mode_info* previous, sub_mode_info* current )
{
	int n_return_value = -1;
	if ( ( !previous ) || ( !current ) ) return ( n_return_value );
	if ( memcmp ( previous, current, sizeof ( sub_mode_info ) ) ) n_return_value = 0;
	else n_return_value = 1;

	return ( n_return_value );
}

/* --- @display_sub_mode@ --- *
 *
 * Arguments:   @sub_mode_info* current@ = current block mode information
 *
 * Returns:     ---

 * Use:         Displays the sub mode information.
 */
void display_sub_mode ( sub_mode_info* current )
{
	printf("File Number : %d\n", current -> file_number );
	printf("Channel	    : %d\n", current -> channel );
	printf("Coding 	    : %d\n", current -> coding );
							
	if ( current -> eof ) printf ( "| End of File |" );
	if ( current -> realtime ) printf ( "| Real Time |" );
	printf ( "| Form %d |", current -> sub_mode );
	if ( current -> trigger ) printf ( "| TRIGGER |" );
	if ( current -> data ) printf ( "| DATA |" );
	if ( current -> audio ) printf ( "| AUDIO |" );
	if ( current -> video ) printf ( "| VIDEO |" );
	if ( current -> eor ) printf ( "| END OF RECORD |" );
	printf("\n");									
}

/* --- @display_mode_info@ --- *
 *
 * Arguments:   @unsigned char* buffer@ = pointer to the buffer
 *              @image_struct *img_struct@ = pointer struct of type image and pregap of image
 *		@sub_mode_info* previous@ = previous block mode information
 *		@off_t block_number@ = block number from the start
 *		@off_t n_loop@ = number of byte from where the block starts
 *
 * Returns:     Zeor on success, @-1@ on error.

 * Use:         Displays the mode information.
 */
int display_mode_info ( unsigned char* buffer, image_struct*  img_struct, sub_mode_info* previous, off_t block_number, off_t n_loop )
{
	/* SYNCH HEADER */
        unsigned const char HEADER_ID [ 12 ] = { 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00 };

	sub_header_block        sub_header; /* Sub Header */
	msf_mode_block 		msf_block;
	copy_sub_header		copy_header;

	sub_mode_info		current;

	int     n_return_value = ERROR;

	if ( !img_struct ) return ( n_return_value );
	
	memset ( &sub_header, 0, sizeof ( sub_header ) );
	memset ( &current, 0, sizeof ( sub_mode_info ) );

	switch ( img_struct -> block ) {
		case 2048: n_return_value = AOK; break;
		case 2336: 
			memmove ( &sub_header, buffer, sizeof ( sub_header_block ) );

			if ( !memcmp ( (unsigned char*) sub_header.first_copy,  sub_header.second_copy, 4 ) )	{
				memmove ( &copy_header, ( unsigned char* ) sub_header.first_copy, sizeof ( copy_header ) );

				current . mode = 2;
				current . file_number = * ( copy_header.file );
				current . channel = *( copy_header.channel );
				current . coding = *( copy_header.coding );
				current . sub_mode = ( ( (int) *(copy_header.sub_mode) ) & 0x20 ) ? 2 : 1;
				current . eof = ( ( *( copy_header.sub_mode ) & SUB_MODE_EOF )  == SUB_MODE_EOF ) ? 1 : 0;
				current . realtime = ( ( *( copy_header.sub_mode ) & SUB_MODE_RT ) == SUB_MODE_RT ) ? 1 : 0;
				current . trigger = ( ( *( copy_header.sub_mode ) & SUB_MODE_TRIGGER ) == SUB_MODE_TRIGGER ) ? 1 : 0;
				current . data = ( ( *( copy_header.sub_mode ) & SUB_MODE_DATA ) == SUB_MODE_DATA ) ? 1 : 0;
				current . audio = ( ( *( copy_header.sub_mode ) & SUB_MODE_AUDIO ) == SUB_MODE_AUDIO ) ? 1 : 0;
				current . video = ( ( *( copy_header.sub_mode ) & SUB_MODE_VIDEO ) == SUB_MODE_VIDEO ) ? 1 : 0;
				current . eor = ( ( *( copy_header.sub_mode ) & SUB_MODE_EOR ) == SUB_MODE_EOR ) ? 1 : 0;

				if ( !( is_same_previous_content ( previous, &current ) ) ) {
					printf ( "Mode %d at (%lld)", current . mode, n_loop );
					lba2msf ( block_number, &msf_block );
                                      	printf("\t%02d:%02d:%02d\n", *( msf_block.minute ), *( msf_block.second ), *( msf_block.frame ) );
					display_sub_mode ( &current );
				}
				memmove ( previous, &current, sizeof ( sub_mode_info ) );
			} 

			n_return_value = AOK; break;
		case 2352:
		case 2448:	 
			memset ( &msf_block, 0, sizeof ( msf_block ) ); 
			if ( !memcmp ( buffer, HEADER_ID, 12 ) ) {
				memmove ( &msf_block, buffer + 12, sizeof ( msf_mode_block ) );
				memmove ( &sub_header, buffer + 16, sizeof ( sub_header_block ) );
			}
			switch ( *( msf_block.mode ) ) {
				case 0: break;
				case 1:
					/* Mode 1 */
					current . mode = *( msf_block.mode );
					if ( !( is_same_previous_content ( previous, &current ) ) ) {
						lba2msf ( block_number, &msf_block ); /* set right msf */
						printf ("Mode %d at (%lld)", current . mode, n_loop );
						printf("\t%02d:%02d:%02d\n", *( msf_block.minute ), *( msf_block.second ), *( msf_block.frame ) );
						memmove ( previous, &current, sizeof ( sub_mode_info ) );
					}
					break;
				case 2:	
					/* Mode 2 */
					if ( !memcmp ( (unsigned char*) sub_header.first_copy,  sub_header.second_copy, 4 ) )	{
						memmove ( &copy_header, ( unsigned char* ) sub_header.first_copy, sizeof ( copy_header ) );

						current . mode = *( msf_block.mode );
						current . file_number = * ( copy_header.file );
						current . channel = *( copy_header.channel );
						current . coding = *( copy_header.coding );
						current . sub_mode = ( ( (int) *(copy_header.sub_mode) ) & 0x20 ) ? 2 : 1;
						current . eof = ( ( *( copy_header.sub_mode ) & SUB_MODE_EOF )  == SUB_MODE_EOF ) ? 1 : 0;
						current . realtime = ( ( *( copy_header.sub_mode ) & SUB_MODE_RT ) == SUB_MODE_RT ) ? 1 : 0;
						current . trigger = ( ( *( copy_header.sub_mode ) & SUB_MODE_TRIGGER ) == SUB_MODE_TRIGGER ) ? 1 : 0;
						current . data = ( ( *( copy_header.sub_mode ) & SUB_MODE_DATA ) == SUB_MODE_DATA ) ? 1 : 0;
						current . audio = ( ( *( copy_header.sub_mode ) & SUB_MODE_AUDIO ) == SUB_MODE_AUDIO ) ? 1 : 0;
						current . video = ( ( *( copy_header.sub_mode ) & SUB_MODE_VIDEO ) == SUB_MODE_VIDEO ) ? 1 : 0;
						current . eor = ( ( *( copy_header.sub_mode ) & SUB_MODE_EOR ) == SUB_MODE_EOR ) ? 1 : 0;

						if ( !( is_same_previous_content ( previous, &current ) ) ) {
							lba2msf ( block_number, &msf_block ); /* set right msf */
							printf ( "Mode %d Form %d at (%lld)", current . mode, current . sub_mode, n_loop );
                                                	printf("\t%02d:%02d:%02d\n", *( msf_block.minute ), *( msf_block.second ), *( msf_block.frame ) );
							display_sub_mode ( &current );
						}
						memmove ( previous, &current, sizeof ( sub_mode_info ) );

					} else {
						current . mode = *( msf_block.mode );

						if ( !( is_same_previous_content ( previous, &current ) ) ) {
							printf ( "Mode %d Formless at (%lld)", current . mode, n_loop );
                                                	printf("\t%02d:%02d:%02d\n", *( msf_block.minute ), *( msf_block.second ), *( msf_block.frame ) );
							display_sub_mode ( &current );
						}
						memmove ( previous, &current, sizeof ( sub_mode_info ) );
					}
					n_return_value = AOK; break;
				default: n_return_value = ERROR; break;
			}
			break;
	}

	return ( n_return_value );
}

/* --- @debug@ --- *
 *
 * Arguments:   @file_ptrs *fptrs@ = pointer struct of source and destination file
 *              @image_struct *img_struct@ = pointer struct of type image and pregap of image
 *
 * Returns:     Zeor on success, @-1@ on error.

 * Use:         Return the detection of the image.
 */
int debug ( file_ptrs* fptrs,  image_struct*  img_struct )
{
	off_t   		n_loop = 0;
        off_t   		img_size = 0;
	off_t			block_number = 0;
	int			pvd_info = 0;
	iso_primary_descriptor	pvd;	 /* Volume Descriptor */
	/*iso_vd_primary		pvd;*/
	sub_mode_info		previous;
	unsigned char*	buffer = NULL;
	
	/* SYNCH HEADER */
        unsigned const char HEADER_ID [ 12 ] = { 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00 };

	if ( ( !fptrs ) || ( !img_struct ) )return ( -1 );

	n_loop = img_struct -> pregap;
	buffer = ( unsigned char* ) malloc ( sizeof ( unsigned char ) * img_struct -> block );
	memset ( &previous, 0, sizeof ( sub_mode_info ) );

	if ( NULL != buffer ) {

		if ( ( img_size = get_file_size ( fptrs -> fsource ) ) < 1 ) return ( -1 ); /* The image file is empty */
	
		printf ( "%s v%s\n", PACKAGE_NAME, VERSION );
		printf ( "Pregap\t: (%ld)\n", img_struct->pregap );	
		printf ( "Block\t: (%d)\n", img_struct->block );
		printf ( "Size\t: (%lld) bytes\n", img_size );


		while ( n_loop < img_size ) {

			set_file_pointer ( fptrs -> fsource, ( n_loop ) );
			fread ( buffer, 1, img_struct -> block, fptrs -> fsource );
			
			if ( 16 == block_number ) {
				
				memset ( &pvd, 0, sizeof ( iso_primary_descriptor ) );
				
				if ( !memcmp ( buffer, HEADER_ID, 12 ) ) {
					/* 2448, 2352 Block */
					if ( !memcmp ( buffer + 16, buffer + 20, 4 ) ) pvd_info = 24;
					else pvd_info = 16;
				} else if ( !memcmp ( buffer, buffer + 4, 4 ) ) pvd_info = 8; /* 2336 Block */
				else pvd_info = 0; /* 2048 Block */
				
				memmove ( &pvd, buffer + pvd_info, sizeof ( iso_primary_descriptor ) );
				display_pvd_info ( &pvd );
				printf ( "\n" );
			}

			display_mode_info ( buffer, img_struct, &previous, block_number, n_loop );

			n_loop += img_struct -> block;
			block_number++;
		}

		free ( buffer );
	}

	return ( 0 );
}
