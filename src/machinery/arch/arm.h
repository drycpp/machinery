/* This is free and unencumbered software released into the public domain. */

#ifndef MACHINERY_ARCH_ARM_H
#define MACHINERY_ARCH_ARM_H

/**
 * @file
 *
 * ARMv8 architecture support.
 *
 * @see http://en.wikipedia.org/wiki/ARM_architecture
 * @see http://en.wikipedia.org/wiki/ARM_architecture#ARMv8
 * @see http://www.arm.com/products/processors/armv8-architecture.php
 */

#include "arm/emitter.h"
#include "arm/encoding.h"

namespace machinery {
  namespace arch {
    namespace arm {
      using emitter = arm_emitter<class Buffer>; // FIXME
    }
  }
}

#endif /* MACHINERY_ARCH_ARM_H */
