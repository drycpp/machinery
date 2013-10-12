/* This is free and unencumbered software released into the public domain. */

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include "compiler.h"

#include <cassert>   /* for assert() */
#include <cstring>   /* for std::strcmp() */
#include <stdexcept> /* for std::invalid_argument */

using namespace machinery::jit;

std::unique_ptr<compiler>
machinery::jit::compiler_for(const char* const target) {
  assert(target != nullptr);
  (void)target;

#ifndef DISABLE_ARM
  if (std::strcmp(target, "armv8-aarch64") == 0) {
    return compiler_for_armv8_aarch64();
  }
#endif

#ifndef DISABLE_MIPS
  if (std::strcmp(target, "mips32") == 0) {
    return compiler_for_mips32();
  }
#endif

#ifndef DISABLE_X86
  if (std::strcmp(target, "x86-64") == 0) {
    return compiler_for_x86_64();
  }
#endif

  throw std::invalid_argument("unknown JIT compilation target");
}

compiler::~compiler() noexcept = default;
