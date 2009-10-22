
AM_CPPFLAGS = -I$(srcdir)/../lib
lib_LTLIBRARIES = libiat.la

libiat_la_SOURCES =   util.c \
		calculate_pregap.c \
      		convert_2_iso.c \
		debug.c \
		mkcue.c \
		mktoc.c \
		mkcore.c 


libiat_la_LDFLAGS = -version-info 0:0:0

bin_PROGRAMS = iat
iat_SOURCES = main.c \
	      cmdline.c


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

iat_LDADD = libiat.la

AM_CFLAGS = -D_FILE_OFFSET_BITS=64 -pedantic -Wconversion -Wpointer-arith -Wcast-align -std=gnu99 

