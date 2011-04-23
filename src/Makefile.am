AM_CFLAGS       = -std=gnu99 -pedantic -pipe
AM_CPPFLAGS     = -D_GNU_SOURCE -D_REENTRANT
AM_LDFLAGS      = -rdynamic
LDADD           = libmachinery.la
lib_LTLIBRARIES = libmachinery.la

libmachinery_la_SOURCES = machinery.c \
  arm.c mips.c ppc.c sparc.c x86.c \
  elf.c

include_HEADERS = machinery.h
pkginclude_HEADERS = \
  arm.h mips.h ppc.h sparc.h x86.h \
  elf.h
