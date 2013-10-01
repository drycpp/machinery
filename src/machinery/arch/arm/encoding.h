/* This is free and unencumbered software released into the public domain. */

#ifndef MACHINERY_ARCH_ARM_ENCODING_H
#define MACHINERY_ARCH_ARM_ENCODING_H

/**
 * @file
 *
 * ARMv8 A64 instruction encoding.
 */

#include <cstdint> /* for std::uint*_t */

namespace machinery {
  namespace arch {
    enum class arm_cc : std::uint8_t;
    union arm_imm7;
  }
}

/**
 * ARMv8 A64 condition codes.
 */
enum class machinery::arch::arm_cc : std::uint8_t {
  eq = 0,  /* 0b0000 */
  ne = 1,  /* 0b0001 */
  hs = 2,  /* 0b0010 */
  lo = 3,  /* 0b0011 */
  mi = 4,  /* 0b0100 */
  pl = 5,  /* 0b0101 */
  vs = 6,  /* 0b0110 */
  vc = 7,  /* 0b0111 */
  hi = 8,  /* 0b1000 */
  ls = 9,  /* 0b1001 */
  ge = 10, /* 0b1010 */
  lt = 11, /* 0b1011 */
  gt = 12, /* 0b1100 */
  le = 13, /* 0b1101 */
  al = 14, /* 0b1110 */
  nv = 15, /* 0b1111 */
};

/**
 * 7-bit unsigned immediate value, in the range 0..127.
 */
union machinery::arch::arm_imm7 final {
  std::uint8_t u8;

  /**
   * Constructor.
   *
   * @param value the immediate value
   */
  arm_imm7(const std::uint8_t value) noexcept
    : u8(value) {
    //assert(value <= 0x7F);
  }
};

#endif /* MACHINERY_ARCH_ARM_ENCODING_H */
