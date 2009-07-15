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

#ifdef HAVE_CONFIG_H
#include "../config.h"
#endif

#ifndef DEFINE_H
#include "define.h"
#endif

#ifndef CMDLINE_H
#include "cmdline.h"
#endif

#ifndef CALCULATE_PREGAP_H
#include "calculate_pregap.h"
#endif

#ifndef CONVERT_2_ISO_H
#include "convert_2_iso.h"
#endif

#ifndef DEBUG_H
#include "debug.h"
#endif

#ifndef MKCUE_H
#include "mkcue.h"
#endif

int main ( int argc, char* argv [ ] )
{
	iat_parser iat_option;
	image_struct img_struct = { 0 };
	file_ptrs fptrs = { 0 };

	int block;
	
	char* file_input = NULL;	/* input image file */
	char* file_desc = NULL;		/* output descriptor file */	
	char* file_output = NULL;	/* output image file */

	
	if ( ( cmdline_parser ( argc, argv, &iat_option ) != 0 ) || ( argc <= 1 ) ) {
		fprintf( stderr,"Run %s --help to see the list of options.\n", argv [ 0 ] ) ;
		exit ( 1 ) ;
	} 
	
	if ( iat_option.help_given ) {
		cmdline_parser_print_help();
		exit ( 0 );
	}
	
	if ( iat_option.version_given ) {
		printf ( "%s v%s\n", PACKAGE_NAME, VERSION );
		exit ( 0 );
	}
  
	if ( iat_option.input_given ) {
		
		file_input = copy_string ( iat_option.input_arg );
	
		if ( ( fptrs.fsource = fopen ( file_input, "rb" ) ) == NULL ) {
			fprintf ( stderr, "%s: %s\n", iat_option.input_arg, strerror ( errno ) ) ;
			free_allocated_memory ( ( void* ) file_input );
			exit ( 1 );
		}	
	} else {
		fprintf ( stderr, "Run %s --help to see the list of options.\n", argv [ 0 ] );
		exit ( 1 );
	}

	if ( iat_option.debug_given ) {
		printf ( "Get info from %s :\n", iat_option.input_arg );		
		
		calculate_pregap ( &fptrs, &img_struct );
		debug ( &fptrs, &img_struct );
		free_allocated_memory ( ( void* ) file_input ); 
		exit ( 0 ) ;
	}
	
	if ( iat_option.toc_given ) {
	
		printf ( "Get info from %s :\n", iat_option.input_arg );		
		
		calculate_pregap ( &fptrs, &img_struct );
		
		if ( img_struct.pregap > 0  ) {	
		
			printf ( "Image conversion :\n\t%s => ", file_input ); 
			
			if ( iat_option.output_given ) {
				file_output = copy_string ( iat_option.output_arg );
				file_output = smart_name ( file_output, "dat" );
			}
			else 	file_output = smart_name ( file_input, "dat" );

				
			if ( ( fptrs.fdest = fopen ( file_output, "wb" ) ) == NULL ) {
				fprintf ( stderr, "%s: %s\n", file_desc, strerror ( errno ) ) ;
				exit ( 1 );
			}

			printf( "%s\n", file_output );	

			
			/* Convert your image for work with cue sheet file */
			if ( ! ( img_2_bin ( &fptrs,  img_struct.block, img_struct.block, img_struct.pregap ) ) )
				{
					printf ("ERROR\n");
					exit ( 0 );
				}

			if ( fptrs.fsource ) fclose ( fptrs.fsource );
			if ( fptrs.fdest ) fclose ( fptrs.fdest );				
			
			if ( ( fptrs.fsource = fopen ( file_output, "rb" ) ) == NULL ) {
				fprintf ( stderr, "%s: %s\n", file_input, strerror ( errno ) ) ;
				exit ( 1 ); 
			}
			
			file_input = copy_string ( file_output );


			
		}

		/* Take name from original file for create name for toc */
		
		if ( iat_option.output_given ) {
			file_desc = copy_string ( iat_option.output_arg );
			file_desc = smart_name ( file_desc, "toc" );
		}
		else file_desc = smart_name ( file_input, "toc" );
		
		printf ("Create %s from %s\n", file_desc, file_input);

		/* Create toc file */
		if ( ( fptrs.fdesc = fopen ( file_desc, "wb" ) ) == NULL ) {
			fprintf ( stderr, "%s: %s\n", file_desc, strerror ( errno ) ) ;
			exit ( 1 );
		}	
		
		create_toc ( &fptrs, &img_struct, file_input );

		free_allocated_memory ( ( void* ) file_input ); 
		free_allocated_memory ( ( void* ) file_desc ); 

		exit ( 0 );
				
	}	

	if ( iat_option.cue_given ) {
	
		printf ( "Get info from %s :\n", iat_option.input_arg );		
	
		calculate_pregap ( &fptrs, &img_struct );

		if ( ( img_struct.pregap > 0 ) || ( img_struct.block >= 2448 ) ) {
			
			printf ( "Image conversion :\n\t%s => ", file_input ); 
			
			if ( iat_option.output_given ) {
				file_output = copy_string ( iat_option.output_arg );
				file_output = smart_name ( file_output, "bin" );
			}
			else 	file_output = smart_name ( file_input, "bin" );

			
			if ( ( fptrs.fdest = fopen ( file_output, "wb" ) ) == NULL ) {
				fprintf ( stderr, "%s: %s\n", file_desc, strerror ( errno ) ) ;
				exit ( 1 );
			}

			printf( "%s", file_output );	

			if ( img_struct.block == 2448 ) {
				printf ( "\n\tWarning: Your image change from 2448 to 2352");
				block = 2352;
			}
			else block = img_struct.block;
			
			printf ("\n");
			
			/* Convert your image for work with cue sheet file */
			if ( ! ( img_2_bin ( &fptrs,  img_struct.block, block, img_struct.pregap ) ) )
				{
					printf ("ERROR\n");
					exit ( 0 );
				}

			if ( fptrs.fsource ) fclose ( fptrs.fsource );
			if ( fptrs.fdest ) fclose ( fptrs.fdest );				
			
			if ( ( fptrs.fsource = fopen ( file_output, "rb" ) ) == NULL ) {
				fprintf ( stderr, "%s: %s\n", file_input, strerror ( errno ) ) ;
				exit ( 1 ); 
			}
			
			file_input = copy_string ( file_output );
				
		}				
			
		/* Take name from original file for create name for cue */
		
		if ( iat_option.output_given ) {
			file_desc = copy_string ( iat_option.output_arg );
			file_desc = smart_name ( file_desc, "cue" );
		}
		else file_desc = smart_name ( file_input, "cue" );
		
		printf ("Create %s from %s\n", file_desc, file_input);

		/* Create cue file */
		if ( ( fptrs.fdesc = fopen ( file_desc, "wb" ) ) == NULL ) {
			fprintf ( stderr, "%s: %s\n", file_desc, strerror ( errno ) ) ;
			exit ( 1 );
		}	

		create_cue ( &fptrs, &img_struct, file_input ) ;

		if ( fptrs.fdesc ) fclose ( fptrs.fdesc );	
		if ( fptrs.fsource ) fclose ( fptrs.fsource );

		free_allocated_memory ( ( void* ) file_input ); 
		free_allocated_memory ( ( void* ) file_desc ); 

		exit ( 0 );
	}	
/* 
	if ( iat_option.output_given ) {
		if ( ( fptrs.fdest = fopen ( iat_option.output_arg, "wb" ) ) == NULL ) {
       			fprintf ( stderr, "%s: %s\n", iat_option.output_arg, strerror ( errno ) ) ;
                        exit ( 1 );
                }
	} else {
                fprintf ( stderr, "Run %s --help to see the list of options.\n", argv [ 0 ] );
                exit ( 1 );
        }
*/
	if ( iat_option.iso_given ) {

		if ( iat_option.output_given ) {
			file_output = copy_string ( iat_option.output_arg );
		}
		else file_output =  smart_name ( file_input, "iso" );

		
		if ( ( fptrs.fdest = fopen ( file_output, "wb" ) ) == NULL ) {
			fprintf ( stderr, "%s: %s\n", file_output, strerror ( errno ) ) ;
                        exit ( 1 );
		}

		calculate_pregap ( &fptrs, &img_struct );

		printf ("Create %s from %s\n", file_output, file_input);

		if ( ( img_struct . pregap == 0 ) &&  ( ( img_struct . type == IMG_ISO ) || ( img_struct . type == IMG_VCD ) ) ) {
		
			switch ( img_struct . type ) {
			
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

			switch ( img_struct . type ) {
				
				case IMG_ISO :
					img_2_iso ( &fptrs, &img_struct );
					break;
					
				case IMG_RAW :
					bin_2_iso ( &fptrs, &img_struct );
					break;
					
				case IMG_VCD :  case 9  : case 10 :
					printf ( "Warning : VCD Image conversion, may not work in your standalone player \n" );	
					bin_2_iso ( &fptrs, &img_struct );
					break;
				
				default :
					printf ( "No DATA found\n" );
					break;
			}
		}
	}
	
	
	if ( fptrs.fsource ) fclose ( fptrs.fsource );
	if ( fptrs.fdest ) fclose ( fptrs.fdest );

/*	
	free ( file_desc ); 
	free ( file_input );

*/
	
	return ( 0 );
}
