lib_LTLIBRARIES = libmachinery.la

libmachinery_la_SOURCES = \
  extern.cc               \
  feature.cc              \
  module.cc               \
  version.cc

pkgincludedir = $(includedir)/machinery
base_pkgincludedir = $(pkgincludedir)

base_pkginclude_HEADERS = \
  extern.h                \
  feature.h               \
  module.h                \
  version.h

nobase_pkginclude_HEADERS =

if !DISABLE_ARM
  nobase_pkginclude_HEADERS += arch/arm.h
endif

if !DISABLE_X86
  nobase_pkginclude_HEADERS += \
    arch/x86.h                 \
    arch/x86/emitter.h         \
    arch/x86/register.h        \
    arch/x86-64.h
  libmachinery_la_SOURCES   += \
    arch/x86/emitter.cc        \
    arch/x86/register.cc
endif
