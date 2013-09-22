/* This is free and unencumbered software released into the public domain. */

#ifndef MACHINERY_ARCH_X86_ENCODING_H
#define MACHINERY_ARCH_X86_ENCODING_H

/**
 * @file
 *
 * x86 instruction encoding.
 */

#include <cstdint> /* for std::uint*_t */

namespace machinery {
  namespace arch {
    union x86_imm8;
    union x86_imm16;
    union x86_imm32;
    union x86_imm64;

    /** x86 opcode byte */
    using x86_opcode = std::uint8_t;

    using x86_reg = std::uint8_t;
    enum class x86_reg8  : x86_reg;
    enum class x86_reg16 : x86_reg;
    enum class x86_reg32 : x86_reg;
    enum class x86_reg64 : x86_reg;
  }
}

/**
 * 8-bit immediate value.
 */
union machinery::arch::x86_imm8 final {
  std::uint8_t u8;

  /**
   * Constructor.
   *
   * @param value the immediate value
   */
  explicit x86_imm8(const std::uint8_t value) noexcept
    : u8(value) {}
};

/**
 * 16-bit immediate value.
 */
union machinery::arch::x86_imm16 final {
  std::uint16_t u16;
  std::uint8_t u8[2];

  /**
   * Constructor.
   *
   * @param value the immediate value
   */
  explicit x86_imm16(const std::uint16_t value) noexcept
    : u16(value) {}
};

/**
 * 32-bit immediate value.
 */
union machinery::arch::x86_imm32 final {
  std::uint32_t u32;
  std::uint8_t u8[4];

  /**
   * Constructor.
   *
   * @param value the immediate value
   */
  explicit x86_imm32(const std::uint32_t value) noexcept
    : u32(value) {}
};

/**
 * 64-bit immediate value.
 */
union machinery::arch::x86_imm64 final {
  std::uint64_t u64;
  std::uint8_t u8[8];

  /**
   * Constructor.
   *
   * @param value the immediate value
   */
  explicit x86_imm64(const std::uint64_t value) noexcept
    : u64(value) {}
};

/**
 * x86 general-purpose registers (8-bit)
 */
enum class machinery::arch::x86_reg8 : machinery::arch::x86_reg {
  AL = 0,  /* 0b000 */
  CL,      /* 0b001 */
  DL,      /* 0b010 */
  BL,      /* 0b011 */
  AH,      /* 0b100 */
  CH,      /* 0b101 */
  DH,      /* 0b110 */
  BH,      /* 0b111 */
};

/**
 * x86 general-purpose registers (16-bit)
 */
enum class machinery::arch::x86_reg16 : machinery::arch::x86_reg {
  AX = 0,  /* 0b000 */
  CX,      /* 0b001 */
  DX,      /* 0b010 */
  BX,      /* 0b011 */
  SP,      /* 0b100 */
  BP,      /* 0b101 */
  SI,      /* 0b110 */
  DI,      /* 0b111 */
};

/**
 * x86 general-purpose registers (32-bit)
 */
enum class machinery::arch::x86_reg32 : machinery::arch::x86_reg {
  EAX = 0, /* 0b000 */
  ECX,     /* 0b001 */
  EDX,     /* 0b010 */
  EBX,     /* 0b011 */
  ESP,     /* 0b100 */
  EBP,     /* 0b101 */
  ESI,     /* 0b110 */
  EDI,     /* 0b111 */
};

/**
 * x86 general-purpose registers (64-bit)
 */
enum class machinery::arch::x86_reg64 : machinery::arch::x86_reg {
  RAX = 0, /* 0b000 */
  RCX,     /* 0b001 */
  RDX,     /* 0b010 */
  RBX,     /* 0b011 */
  RSP,     /* 0b100 */
  RBP,     /* 0b101 */
  RSI,     /* 0b110 */
  RDI,     /* 0b111 */
  R8,
  R9,
  R10,
  R11,
  R12,
  R13,
  R14,
  R15,
};

#endif /* MACHINERY_ARCH_X86_ENCODING_H */
