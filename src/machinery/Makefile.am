lib_LTLIBRARIES = libmachinery.la

libmachinery_la_SOURCES = \
  extern.cc               \
  feature.cc              \
  module.cc               \
  version.cc              \
  util/buffer.cc

pkgincludedir = $(includedir)/machinery
base_pkgincludedir = $(pkgincludedir)

base_pkginclude_HEADERS = \
  extern.h                \
  feature.h               \
  module.h                \
  version.h               \
  bits/word.h             \
  util/buffer.h

nobase_pkginclude_HEADERS =

if !DISABLE_ARM
  nobase_pkginclude_HEADERS += \
    arch/arm.h                 \
    arch/arm/emitter.h         \
    arch/arm/encoding.h        \
    arch/armv8.h
  libmachinery_la_SOURCES   += \
    arch/arm/compiler.cc       \
    arch/arm/emitter.cc        \
    arch/arm/encoding.cc
endif

if !DISABLE_MIPS
  nobase_pkginclude_HEADERS += \
    arch/mips.h                \
    arch/mips32.h              \
    arch/mips32/emitter.h      \
    arch/mips32/encoding.h
  libmachinery_la_SOURCES   += \
    arch/mips32/compiler.cc    \
    arch/mips32/emitter.cc     \
    arch/mips32/encoding.cc
endif

if !DISABLE_X86
  nobase_pkginclude_HEADERS += \
    arch/x86.h                 \
    arch/x86/emitter.h         \
    arch/x86/encoding.h        \
    arch/x86-64.h
  libmachinery_la_SOURCES   += \
    arch/x86/compiler.cc       \
    arch/x86/emitter.cc        \
    arch/x86/encoding.cc
endif

if !DISABLE_IR
  base_pkginclude_HEADERS += ir.h
  libmachinery_la_SOURCES += ir.cc
endif

if !DISABLE_JIT
  base_pkginclude_HEADERS +=   \
    jit.h                      \
    jit/compiler.h
  libmachinery_la_SOURCES +=   \
    jit/compiler.cc
endif
