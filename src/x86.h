/* This is free and unencumbered software released into the public domain. */

#ifndef _MACHINERY_X86_H
#define _MACHINERY_X86_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <unistd.h>   /* for ssize_t */

/* x86 prefix byte */
typedef uint8_t x86_prefix_t;

/* x86 opcode byte */
typedef uint8_t x86_opcode_t;

/* x86 ModR/M byte */
typedef struct {
  int rm  : 3;   /* R/M (bits 0..2) */
  int reg : 3;   /* reg/opcode (bits 3..5)*/
  int mod : 2;   /* mod (bits 6..7) */
} x86_modrm_t;

/* x86 SIB (Scale-Index-Base) byte */
typedef struct {
  int base  : 3; /* base register number (bits 0..2) */
  int index : 3; /* index register number (bits 3..5) */
  int scale : 2; /* scale factor (bits 6..7) */
} x86_sib_t;

/* x86 address displacements */
typedef int8_t  x86_disp8_t;
typedef int16_t x86_disp16_t;
typedef int32_t x86_disp32_t;
typedef union {
  x86_disp8_t  b;
  x86_disp16_t w;
  x86_disp32_t l;
} x86_disp_t;

/* x86 immediate operands */
typedef int8_t  x86_imm8_t;
typedef int16_t x86_imm16_t;
typedef int32_t x86_imm32_t;

/* x86 instruction formats */
typedef union {
  x86_opcode_t opcode;
} x86_insn_t;

#ifdef __cplusplus
}
#endif

#endif /* _MACHINERY_X86_H */
