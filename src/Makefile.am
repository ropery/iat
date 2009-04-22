bin_PROGRAMS = iat
iat_SOURCES =   util.c \
		calculate_pregap.c \
      		convert_2_iso.c \
      		cmdline.c \
   		main.c 
include_HEADERS = util.h \
		calculate_pregap.h \
		convert_2_iso.h \
		cmdline.h \
		define.h \
		mmc2r11.h 

AM_CFLAGS = -D_FILE_OFFSET_BITS=64 -pedantic -Wconversion -Wpointer-arith -Wcast-align 

