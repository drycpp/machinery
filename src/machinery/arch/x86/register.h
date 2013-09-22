/* This is free and unencumbered software released into the public domain. */

#ifndef MACHINERY_ARCH_X86_REGISTER_H
#define MACHINERY_ARCH_X86_REGISTER_H

/**
 * @file
 *
 * x86 register structures.
 */

#include <cstdint> /* for std::uint8_t */

namespace machinery {
  namespace arch {
    using x86_opcode = std::uint8_t; /**< x86 opcode byte */
    using x86_reg    = std::uint8_t;
    enum class x86_reg8  : x86_reg;
    enum class x86_reg16 : x86_reg;
    enum class x86_reg32 : x86_reg;
    enum class x86_reg64 : x86_reg;
  }
}

/**
 * x86 general-purpose registers (8-bit)
 */
enum class machinery::arch::x86_reg8 : machinery::arch::x86_reg {
  X86_REG_AL = 0,  /* 0b000 */
  X86_REG_CL,      /* 0b001 */
  X86_REG_DL,      /* 0b010 */
  X86_REG_BL,      /* 0b011 */
  X86_REG_AH,      /* 0b100 */
  X86_REG_CH,      /* 0b101 */
  X86_REG_DH,      /* 0b110 */
  X86_REG_BH,      /* 0b111 */
};

/**
 * x86 general-purpose registers (16-bit)
 */
enum class machinery::arch::x86_reg16 : machinery::arch::x86_reg {
  X86_REG_AX = 0,  /* 0b000 */
  X86_REG_CX,      /* 0b001 */
  X86_REG_DX,      /* 0b010 */
  X86_REG_BX,      /* 0b011 */
  X86_REG_SP,      /* 0b100 */
  X86_REG_BP,      /* 0b101 */
  X86_REG_SI,      /* 0b110 */
  X86_REG_DI,      /* 0b111 */
} x86_reg16_t;

/**
 * x86 general-purpose registers (32-bit)
 */
enum class machinery::arch::x86_reg32 : machinery::arch::x86_reg {
  X86_REG_EAX = 0, /* 0b000 */
  X86_REG_ECX,     /* 0b001 */
  X86_REG_EDX,     /* 0b010 */
  X86_REG_EBX,     /* 0b011 */
  X86_REG_ESP,     /* 0b100 */
  X86_REG_EBP,     /* 0b101 */
  X86_REG_ESI,     /* 0b110 */
  X86_REG_EDI,     /* 0b111 */
};

/**
 * x86 general-purpose registers (64-bit)
 */
enum class machinery::arch::x86_reg64 : machinery::arch::x86_reg {
  X86_REG_RAX = 0, /* 0b000 */
  X86_REG_RCX,     /* 0b001 */
  X86_REG_RDX,     /* 0b010 */
  X86_REG_RBX,     /* 0b011 */
  X86_REG_RSP,     /* 0b100 */
  X86_REG_RBP,     /* 0b101 */
  X86_REG_RSI,     /* 0b110 */
  X86_REG_RDI,     /* 0b111 */
  X86_REG_R8,
  X86_REG_R9,
  X86_REG_R10,
  X86_REG_R11,
  X86_REG_R12,
  X86_REG_R13,
  X86_REG_R14,
  X86_REG_R15,
};

#endif /* MACHINERY_ARCH_X86_REGISTER_H */
