/* This is free and unencumbered software released into the public domain. */

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include "module.h"

static const char* const module_names[] = {
#ifndef DISABLE_ARM
  "arm",
#endif
#ifndef DISABLE_IR
  "ir",
#endif
#ifndef DISABLE_JIT
  "jit",
#endif
#ifndef DISABLE_X86
  "x86",
#endif
};
