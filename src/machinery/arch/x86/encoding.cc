/* This is free and unencumbered software released into the public domain. */

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include "encoding.h"

using namespace machinery::arch;

static_assert(sizeof(x86_imm8) == 1,
  "sizeof(machinery::arch::x86_imm8) != 1");

static_assert(sizeof(x86_imm16) == 2,
  "sizeof(machinery::arch::x86_imm16) != 2");

static_assert(sizeof(x86_imm32) == 4,
  "sizeof(machinery::arch::x86_imm32) != 4");

static_assert(sizeof(x86_imm64) == 8,
  "sizeof(machinery::arch::x86_imm64) != 8");
