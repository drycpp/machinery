/* This is free and unencumbered software released into the public domain. */

#ifndef MACHINERY_ARCH_X86_H
#define MACHINERY_ARCH_X86_H

/**
 * @file
 *
 * x86/x86-64 architecture support.
 *
 * @see http://en.wikipedia.org/wiki/X86
 * @see http://en.wikipedia.org/wiki/X86-64
 * @see http://www.intel.com/content/www/us/en/processors/architectures-software-developer-manuals.html
 * @see http://developer.amd.com/resources/documentation-articles/developer-guides-manuals/
 */

#include "x86/emitter.h"
#include "x86/encoding.h"

namespace machinery {
  namespace arch {
    namespace x86 {
      using emitter = x86_emitter<class Buffer>; // FIXME
      using imm8    = x86_imm8;
      using imm16   = x86_imm16;
      using imm32   = x86_imm32;
      using imm64   = x86_imm64;
      using opcode  = x86_opcode;
      using reg     = x86_reg;
      using reg8    = x86_reg8;
      using reg16   = x86_reg16;
      using reg32   = x86_reg32;
      using reg64   = x86_reg64;
    }
  }
}

#endif /* MACHINERY_ARCH_X86_H */
