#libiat
#AM_CPPFLAGS = -I$(srcdir)/../lib
#
libiat_ladir = $(includedir)/libiat

lib_LTLIBRARIES = libiat.la

libiat_la_SOURCES =   libiat/util.c \
		libiat/calculate_pregap.c \
      		libiat/convert_2_iso.c \
		libiat/debug.c \
		libiat/mkcue.c \
		libiat/mktoc.c \
		libiat/mkcore.c 


libiat_la_LDFLAGS = -version-info 0:0:0



libiat_la_HEADERS = libiat/util.h \
		libiat/calculate_pregap.h \
		libiat/convert_2_iso.h \
		libiat/define.h \
		libiat/mmc2r11.h \
		libiat/debug.h \
		libiat/ecma119.h \
		libiat/mkcue.h \
		libiat/mktoc.h	\
		libiat/mkcore.h \
		libiat/ecma167.h

iat_LDADD = libiat.la


bin_PROGRAMS = iat
iat_SOURCES = main.c \
	      cmdline.c \
	      cmdline.h

AM_CFLAGS = -D_FILE_OFFSET_BITS=64 -pedantic -Wconversion -Wpointer-arith -Wcast-align -std=gnu99 

