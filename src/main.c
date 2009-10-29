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

/* Large File Support */
#define _FILE_OFFSET_BITS 64
#define _LARGEFILE_SOURCE

#include <stdio.h>
#include <errno.h>
#include <string.h>

#ifdef HAVE_CONFIG_H
#include "../config.h"
#endif

#ifndef DEFINE_H
#include "libiat/define.h"
#endif

#ifndef CMDLINE_H
#include "cmdline.h"
#endif

#ifndef CALCULATE_PREGAP_H
#include "libiat/calculate_pregap.h" 
#endif

#ifndef CONVERT_2_ISO_H
#include "libiat/convert_2_iso.h"
#endif

#ifndef DEBUG_H
#include "libiat/debug.h"
#endif

#ifndef MKCUE_H
#include "libiat/mkcue.h"
#endif

#ifndef MKTOC_H
#include "libiat/mktoc.h"
#endif

typedef struct gengetopt_args_info iat_parser; 

#define DAT_FORMAT	0
#define BIN_FORMAT	1

#define TOC_FORMAT	0
#define CUE_FORMAT	1

#define HLP_MODE	0
#define DBG_MODE	1
#define TOC_MODE	2
#define CUE_MODE	3
#define ISO_MODE	4

/* ---@create_file_descriptor@ ---*
*
* Arguments:	@iat_parser* iat_option@ = options from the command line
* 		@image_struct* img_struct@ = the information about the image
* 		@file_ptrs* fptrs@ = the input and the destination file pointers
* 		@int is_cue@ = 1 if it is cue, 0 if toc
*		@int is_filename_change@ = 1 if filename change, 0 otherwise
*
* Returns:	@AOK@ if successful, @ERROR@ otherwise.
*
* Use:		Creates toc (or) cue from the cd image.
*
*/
int create_file_descriptor ( iat_parser* iat_option, image_struct* img_struct, file_ptrs* fptrs, int is_cue , int is_filename_change )
{
	int return_value = ERROR;
	char* file_desc = NULL;
	char* file_descriptor = NULL;
	char ext [ 2 ] [ 4 ] = { 0 };
	char ext_dat_or_bin [ 2 ] [ 4 ] = { 0 };

	if ( ( NULL == iat_option ) || ( NULL == img_struct ) || ( NULL == fptrs ) ) return ( return_value );
	memset ( ext [ 0 ], 0, 4 ); memmove ( ext [ 0 ], "toc", 3 );
	memset ( ext [ 1 ], 0, 4 ); memmove ( ext [ 1 ], "cue", 3 );
	memset ( ext_dat_or_bin [ 0 ], 0, 4 ); memmove ( ext_dat_or_bin [ 0 ], "dat", 3 );
	memset ( ext_dat_or_bin [ 1 ], 0, 4 ); memmove ( ext_dat_or_bin [ 1 ], "bin", 3 );


	if ( 1 == is_filename_change ) {
		if ( iat_option -> output_given ) file_descriptor = copy_string ( iat_option -> output_arg );
		else file_descriptor = smart_name ( iat_option -> input_arg, ext_dat_or_bin [ is_cue ] );
	} else {
		file_descriptor = copy_string ( iat_option -> input_arg );
	}

	if ( NULL != file_descriptor ) {
		char* temp_file_descriptor = NULL;

		if ( AOK == is_windows_file_path ( file_descriptor ) ) temp_file_descriptor = strrchr ( file_descriptor, '\\' );
		else temp_file_descriptor = strrchr ( file_descriptor, '/' );

		if ( NULL != temp_file_descriptor ) temp_file_descriptor++;
		else temp_file_descriptor = file_descriptor;

		if ( ( iat_option -> output_given ) && ( 1 == is_filename_change ) ) {
			file_desc = smart_name ( iat_option -> output_arg, ext [ is_cue ] );
		} else {
			if ( iat_option -> output_given )
				printf ( "Ignoring Output File Name, as convertion NOT required\n" );
			file_desc = smart_name ( iat_option -> input_arg, ext [ is_cue ] );
		}

		/*printf ( "Create %s from %s\n", file_desc, iat_option -> input_arg );*/
		printf ( "Create %s for %s\n", file_desc, file_descriptor );

		if ( ( fptrs -> fdesc = fopen ( file_desc, "wb" ) ) == NULL ) {
			fprintf ( stderr, "%s: %s\n", file_desc, strerror ( errno ) );
			free_allocated_memory ( ( void* ) file_descriptor );
			free_allocated_memory ( ( void* ) file_desc );
			return ( return_value );
		}

		switch ( is_cue ) {
			case TOC_FORMAT :
				create_toc ( fptrs, img_struct, temp_file_descriptor );
				return_value = AOK;
				break;
			case CUE_FORMAT :
				create_cue ( fptrs, img_struct, temp_file_descriptor );
				return_value = AOK;
				break;
			default :
				break;
		}

		free_allocated_memory ( ( void* ) file_desc );
		fclose ( fptrs -> fdesc );
	}

	free_allocated_memory ( ( void* ) file_descriptor );

	return ( return_value );
}

/* ---@create_image@ ---*
*
* Arguments:	@iat_parser* iat_option@ = options from the command line
* 		@image_struct* img_struct@ = the information about the image
* 		@file_ptrs* fptrs@ = the input and the destination file pointers
* 		@int is_bin@ = 1 if it is bin, 0 if dat
*
* Returns:	@AOK@ if successful, @ERROR@ otherwise.
*
* Use:		Creates bin (or) dat from the cd image.
*
*/
int create_image ( iat_parser* iat_option, image_struct* img_struct, file_ptrs* fptrs, int is_bin )
{
	int return_value = ERROR;
	char* file_output = NULL;
	char ext [ 2 ] [ 4 ] = { 0 };
	size_t block = 0;

	if ( ( NULL == iat_option ) || ( NULL == img_struct ) || ( NULL == fptrs ) ) return ( return_value );

	memset ( ext [ 0 ], 0, 4 ); memmove ( ext [ 0 ], "dat", 3 );
	memset ( ext [ 1 ], 0, 4 ); memmove ( ext [ 1 ], "bin", 3 );

	printf ( "Image conversion :\n\t%s => ", iat_option -> input_arg );

	/*if ( iat_option -> output_given ) file_output = smart_name ( iat_option -> output_arg, ext [ is_bin ] );*/
	if ( iat_option -> output_given ) file_output = copy_string ( iat_option -> output_arg );
	else file_output = smart_name ( iat_option -> input_arg, ext [ is_bin ] );

	if ( NULL == ( fptrs -> fdest = fopen ( file_output, "wb" ) ) ) {
		fprintf ( stderr, "%s: %s\n", file_output, strerror ( errno ) );
		free_allocated_memory ( ( void* ) file_output );
		return ( return_value );
	}

	printf( "%s\n", file_output );

	switch ( is_bin ) {
		case DAT_FORMAT :
			block = img_struct -> block;
			if ( img_struct -> block == 2368 ) block = 2048;
			break;
		case BIN_FORMAT :
			block = img_struct -> block;
			if ( img_struct -> block == 2368 ) block = 2048;
			if ( img_struct -> block == 2448 ) block = 2352;

			break;
		default :
			block = 0;
			break;
	}

	printf (" BLOCK : (%d)\n", block );

	if ( AOK != ( img_2_img ( fptrs, img_struct, block ) ) ) {
		printf ("\nERROR");
		free_allocated_memory ( ( void* ) file_output );
		return ( return_value );
	}
	else return_value = AOK;

	/* NEED FIX */
	img_struct -> block = block ;

	fclose ( fptrs -> fdest );
	free_allocated_memory ( ( void* ) file_output );

	return ( return_value );
}

/* ---@iso_conversion@ ---*
*
* Arguments:	@iat_parser* iat_option@ = options from the command line
* 		@image_struct* img_struct@ = the information about the image
* 		@file_ptrs* fptrs@ = the input and the destination file pointers
*
* Returns:	@AOK@ if successful, @ERROR@ otherwise.
*
* Use:		Converts the cd image to Iso9660 image.
*
*/
int iso_conversion ( iat_parser* iat_option, image_struct* img_struct, file_ptrs* fptrs )
{
	int return_value = ERROR;
	char* file_output = NULL;

	if ( ( NULL == iat_option ) || ( NULL == img_struct ) || ( NULL == fptrs ) ) return ( return_value );

	if ( ( img_struct -> pregap == 0 ) &&  ( ( img_struct -> type == IMG_ISO ) || ( img_struct -> type == IMG_VCD ) ) ) {
		switch ( img_struct -> type ) {

			case IMG_ISO :
				printf ( "Warning : ISO iso9660 Image found, convertion not required \n" );
				break;

			case IMG_VCD :
				printf ( "Warning : SVCD ISO iso9660 Image found, convertion not required \n" );
				break;

			default:
				break;
		}
	} else {
		if ( iat_option -> output_given ) file_output = copy_string ( iat_option -> output_arg );
		else file_output =  smart_name ( iat_option -> input_arg, "iso" );

		if ( NULL == ( fptrs -> fdest = fopen ( file_output, "wb" ) ) ) {
			fprintf ( stderr, "%s: %s\n", file_output, strerror ( errno ) );
			free_allocated_memory ( ( void* ) file_output );
			return ( return_value );
		}

		printf ( "Create %s from %s\n", file_output, iat_option -> input_arg );

		switch ( img_struct -> type ) {

			case IMG_ISO :
				printf ( "Block :%d\n", img_struct -> block );
				img_2_iso ( fptrs, img_struct );
				return_value = AOK;
				break;

			case IMG_RAW :
				printf ( "RAW Block :%d\n", img_struct -> block );
				bin_2_iso ( fptrs, img_struct );
				return_value = AOK;
				break;

			case IMG_VCD :  case 9  : case 10 :
				printf ( "Warning : VCD Image conversion, may not work in your standalone player :%d\n", img_struct -> block );
				bin_2_iso ( fptrs, img_struct );
				return_value = AOK;
				break;

			default :
				printf ( "No DATA found\n" );
				break;
		}

		fclose ( fptrs -> fdest );
		free_allocated_memory ( ( void* ) file_output );
	}

	return ( return_value );
}

/* ---@choose_conversion@ ---*
*
* Arguments:	@iat_parser* iat_option@ = options from the command line
*
* Returns:	@{HLP_MODE, DBG_MODE, TOC_MODE, CUE_MODE, ISO_MODE}@.
*
* Use:		Chooses the conversion methods.
*
*/
int choose_conversion ( iat_parser* iat_option )
{
	int return_value = HLP_MODE;

	if ( iat_option -> debug_given ) { return_value = DBG_MODE; }
	else if ( iat_option -> toc_given ) { return_value = TOC_MODE; }
	else if ( iat_option -> cue_given ) { return_value = CUE_MODE; }
	else if ( iat_option -> iso_given ) { return_value = ISO_MODE; }

	return ( return_value );
}

int main ( int argc, char* argv [ ] )
{
	iat_parser iat_option;
	image_struct img_struct = { 0 };
	file_ptrs fptrs = { 0 };

	char* file_input = NULL;	/* input image file */

	int return_value = ERROR;
	int n_value = AOK;

	if ( ( cmdline_parser ( argc, argv, &iat_option ) != 0 ) || ( argc <= 1 ) ) {
		fprintf( stderr,"Run %s --help to see the list of options.\n", argv [ 0 ] );
		cmdline_parser_free (&iat_option);

		exit ( ERROR );
	}

	if ( iat_option.help_given ) {
		cmdline_parser_print_help();
		exit ( AOK );
	}

	if ( iat_option.version_given ) {
		printf ( "%s v%s\n", PACKAGE_NAME, VERSION );
		exit ( AOK );
	}


	if ( iat_option.output_given ) {
		char* temp_file_name = NULL;

		/* Check the validity of the -o or --output filename */
		if ( AOK == is_windows_file_path ( iat_option.output_arg ) ) temp_file_name = strrchr ( iat_option.output_arg, '\\' );
		else temp_file_name = strrchr ( iat_option.output_arg, '/' );

		/* Exit if directory name alone is given */
		if ( NULL != temp_file_name ) {
			if ( '\0' == *( temp_file_name + 1 ) ) {
				printf ( "MISSING OUTPUT FILENAME, only DIRECTORY PATH AVAILABLE\n" );
				exit ( ERROR );
			}
		}
	}

	if ( iat_option.input_given ) {
		char* temp_file_name = NULL;

		/* Check the validity of the -i or --input filename */
		if ( AOK == is_windows_file_path ( iat_option.input_arg ) ) temp_file_name = strrchr ( iat_option.input_arg, '\\' );
		else temp_file_name = strrchr ( iat_option.input_arg, '/' );

		/* Exit if directory name alone is given */
		if ( NULL != temp_file_name ) {
			if ( '\0' == *( temp_file_name + 1 ) ) {
				printf ( "MISSING INUPUT FILENAME, only DIRECTORY PATH AVAILABLE\n" );
				exit ( ERROR );
			}
		}

		file_input = copy_string ( iat_option.input_arg );
		if ( ( fptrs.fsource = fopen ( file_input, "rb" ) ) == NULL ) {
			fprintf ( stderr, "%s: %s\n", iat_option.input_arg, strerror ( errno ) );
			free_allocated_memory ( ( void* ) file_input );
			cmdline_parser_free (&iat_option);

			exit ( ERROR );
		}

		/* If the input is provided, calculate the pregap info */
		printf ( "Get info from %s\n", file_input );
		calculate_pregap ( &fptrs, &img_struct );
	} else {
		fprintf ( stderr, "Run %s --help to see the list of options.\n", argv [ 0 ] );
		cmdline_parser_free (&iat_option);

		exit ( ERROR );
	}
	

	if ( img_struct.type != IMG_UNKOWN ) {

		int is_filename_change = 0;
	
		switch ( choose_conversion ( &iat_option ) ) {
			case HLP_MODE :
					cmdline_parser_print_help();
					return_value = AOK;
					break;
			case DBG_MODE :
					debug ( &fptrs, &img_struct );
					return_value = AOK;
					break;
			case TOC_MODE :
					if ( img_struct.block == 2368 ) {
						printf ( "\nWarning: YOUR IMAGE of %d  will be TRANSFORMED to 2048\n", img_struct.block );

						is_filename_change = 1;

						if ( ! ( iat_option.output_given ) ) {
						
							iat_option.input_arg  =  smart_name ( iat_option.input_arg, "dat" );
							iat_option.output_given = 1;
						}
		
						return_value = iso_conversion ( &iat_option, &img_struct, &fptrs );
					
					}	
					else if ( img_struct.pregap > 0 ) {
						n_value = ( ERROR == create_image ( &iat_option, &img_struct, &fptrs, DAT_FORMAT ) ) ? ERROR : AOK;
						is_filename_change = 1;
						return_value = n_value;
					}

					if ( AOK == n_value )
						return_value = create_file_descriptor ( &iat_option, &img_struct, &fptrs, TOC_FORMAT, is_filename_change );
					break;
			case CUE_MODE :
					if ( ( img_struct.block == 2448 ) || ( img_struct.block == 2368 ) ) {
						printf ( "\nWarning: YOUR IMAGE of %d  will be TRANSFORMED to ", img_struct.block );
					
						if ( img_struct.block == 2368 ) printf ("2048");
						else printf ("2352");
						printf ("\n");
					}
					
					if ( img_struct.block == 2368 ) {

						is_filename_change = 1;

						if ( ! ( iat_option.output_given ) ) {
							iat_option.output_arg  =  smart_name ( iat_option.input_arg, "bin" );
							iat_option.output_given = 1;
						}
					
						return_value = iso_conversion ( &iat_option, &img_struct, &fptrs );
					}
					else if ( ( img_struct.pregap > 0 ) || ( img_struct.block >= 2448 )  ) {
						n_value = ( ERROR == create_image ( &iat_option, &img_struct, &fptrs, BIN_FORMAT ) ) ? ERROR : AOK;
						is_filename_change = 1;
						return_value = n_value;
					}
					
					if ( AOK == n_value )
						return_value = create_file_descriptor ( &iat_option, &img_struct, &fptrs, CUE_FORMAT, is_filename_change );
					break;
			case ISO_MODE :
					return_value = iso_conversion ( &iat_option, &img_struct, &fptrs );
					break;
			default :
					cmdline_parser_print_help();
					return_value = AOK;
					break;
		}
	};

	if ( fptrs.fsource ) fclose ( fptrs.fsource );
	free_allocated_memory ( ( void* ) file_input );
	cmdline_parser_free (&iat_option);

	return ( AOK );
}
