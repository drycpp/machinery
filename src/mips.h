/* This is free and unencumbered software released into the public domain. */

#ifndef _MACHINERY_MIPS_H
#define _MACHINERY_MIPS_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>

/* MIPS registers */
typedef enum {
  MIPS_REG_ZERO = 0,  /* zero value */
  MIPS_REG_AT   = 1,  /* assembly temporary */
  MIPS_REG_V0   = 2,  /* procedure result */
  MIPS_REG_V1,
  MIPS_REG_A0   = 4,  /* procedure arguments */
  MIPS_REG_A1,
  MIPS_REG_A2,
  MIPS_REG_A3,
  MIPS_REG_T0   = 8,  /* temporaries */
  MIPS_REG_T1,
  MIPS_REG_T2,
  MIPS_REG_T3,
  MIPS_REG_T4,
  MIPS_REG_T5,
  MIPS_REG_T6,
  MIPS_REG_T7,
  MIPS_REG_S0   = 16, /* register variables */
  MIPS_REG_S1,
  MIPS_REG_S2,
  MIPS_REG_S3,
  MIPS_REG_S4,
  MIPS_REG_S5,
  MIPS_REG_S6,
  MIPS_REG_S7,
  MIPS_REG_T8   = 24,
  MIPS_REG_T9,
  MIPS_REG_K0   = 26,
  MIPS_REG_K1,
  MIPS_REG_GP   = 28, /* global pointer */
  MIPS_REG_SP   = 29, /* stack pointer */
  MIPS_REG_FP   = 30, /* frame pointer */
  MIPS_REG_RA   = 31, /* return address */
} mips_reg_t;

/* MIPS R-format instruction */
typedef struct {
  int op       : 6;   /* opcode */
  int rs       : 5;   /* first register source operand */
  int rt       : 5;   /* second register source operand */
  int rd       : 5;   /* register destination operand */
  int shamt    : 5;   /* shift amount */
  int funct    : 6;   /* function code */
} mips_r_insn_t;

/* MIPS I-format instruction */
typedef struct {
  int op       : 6;   /* opcode */
  int rs       : 5;
  int rt       : 5;
  int imm      : 16;  /* constant or address */
} mips_i_insn_t;

/* MIPS J-format instruction */
typedef struct {
  int op       : 6;   /* opcode */
  int addr     : 26;  /* address */
} mips_j_insn_t;

/* MIPS instruction */
typedef union {
  mips_r_insn_t r;
  mips_i_insn_t i;
  mips_j_insn_t j;
} mips_insn_t;

#ifdef __cplusplus
}
#endif

#endif /* _MACHINERY_MIPS_H */
