/* This is free and unencumbered software released into the public domain. */

#ifndef MACHINERY_ARCH_MIPS32_H
#define MACHINERY_ARCH_MIPS32_H

/**
 * @file
 *
 * MIPS32 architecture support.
 *
 * @see http://en.wikipedia.org/wiki/MIPS_architecture#MIPS32
 * @see http://www.imgtec.com/mips/mips32-architecture.asp
 */

#include "mips32/emitter.h"
#include "mips32/encoding.h"

namespace machinery {
  namespace arch {
    namespace mips32 {
      using emitter = mips32_emitter<class Buffer>; // FIXME
    }
  }
}

#endif /* MACHINERY_ARCH_MIPS32_H */
