bin_PROGRAMS = iat
iat_SOURCES =   util.c \
		calculate_pregap.c \
      		convert_2_iso.c \
		debug.c \
      		cmdline.c \
		mkcue.c \
		mktoc.c \
		mkcore.c \
		main.c 
noinst_HEADERS = util.h \
		calculate_pregap.h \
		convert_2_iso.h \
		cmdline.h \
		define.h \
		mmc2r11.h \
		debug.h \
		ecma119.h \
		mkcue.h \
		mktoc.h	\
		mkcore.h \
		ecma167.h

AM_CFLAGS = -D_FILE_OFFSET_BITS=64 -pedantic -Wconversion -Wpointer-arith -Wcast-align #-std=c99 

