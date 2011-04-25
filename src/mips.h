/* This is free and unencumbered software released into the public domain. */

#ifndef _MACHINERY_MIPS_H
#define _MACHINERY_MIPS_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <unistd.h>   /* for ssize_t */

/* MIPS field types */
typedef int8_t  mips_op_t;
typedef int8_t  mips_shamt_t;
typedef int8_t  mips_funct_t;
typedef int16_t mips_imm_t;
typedef int32_t mips_addr_t;

/* MIPS general-purpose registers */
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

/* MIPS floating-point registers */
typedef enum {
  MIPS_REG_F0   = 0,
  MIPS_REG_F1,
  MIPS_REG_F2,
  MIPS_REG_F3,
  MIPS_REG_F4,
  MIPS_REG_F5,
  MIPS_REG_F6,
  MIPS_REG_F7,
  MIPS_REG_F8,
  MIPS_REG_F9,
  MIPS_REG_F10,
  MIPS_REG_F11,
  MIPS_REG_F12,
  MIPS_REG_F13,
  MIPS_REG_F14,
  MIPS_REG_F15,
  MIPS_REG_F16,
  MIPS_REG_F17,
  MIPS_REG_F18,
  MIPS_REG_F19,
  MIPS_REG_F20,
  MIPS_REG_F21,
  MIPS_REG_F22,
  MIPS_REG_F23,
  MIPS_REG_F24,
  MIPS_REG_F25,
  MIPS_REG_F26,
  MIPS_REG_F27,
  MIPS_REG_F28,
  MIPS_REG_F29,
  MIPS_REG_F30,
  MIPS_REG_F31,
} mips_reg_f_t;

/* MIPS R-format instruction */
typedef struct {
  int op       : 6;   /* opcode */
  int rs       : 5;   /* first register source operand */
  int rt       : 5;   /* second register source operand */
  int rd       : 5;   /* register destination operand */
  int shamt    : 5;   /* shift amount */
  int funct    : 6;   /* function code */
} mips_insn_r_t;

/* MIPS I-format instruction */
typedef struct {
  int op       : 6;   /* opcode */
  int rs       : 5;
  int rt       : 5;
  int imm      : 16;  /* constant or address */
} mips_insn_i_t;

/* MIPS J-format instruction */
typedef struct {
  int op       : 6;   /* opcode */
  int addr     : 26;  /* address */
} mips_insn_j_t;

/* MIPS instruction */
typedef union {
  mips_insn_r_t r;
  mips_insn_i_t i;
  mips_insn_j_t j;
} mips_insn_t;

/* MIPS instruction encoders */
extern ssize_t mips_encode_r_insn(mips_insn_t* insn, const mips_op_t op, const mips_reg_t rs, const mips_reg_t rt, const mips_reg_t rd, const mips_shamt_t shamt, const mips_funct_t funct);
extern ssize_t mips_encode_i_insn(mips_insn_t* insn, const mips_op_t op, const mips_reg_t rs, const mips_reg_t rt, const mips_imm_t imm);
extern ssize_t mips_encode_j_insn(mips_insn_t* insn, const mips_op_t op, const mips_addr_t addr);

/* MIPS instructions emitters */
extern ssize_t mips_emit_nop(mips_insn_t* insn);
extern ssize_t mips_emit_ssnop(mips_insn_t* insn);
extern ssize_t mips_emit_sync(mips_insn_t* insn);
extern ssize_t mips_emit_add(mips_insn_t* insn, const mips_reg_t rd, const mips_reg_t rs, const mips_reg_t rt);
extern ssize_t mips_emit_addu(mips_insn_t* insn, const mips_reg_t rd, const mips_reg_t rs, const mips_reg_t rt);
extern ssize_t mips_emit_addi(mips_insn_t* insn, const mips_reg_t rd, const mips_reg_t rs, const mips_imm_t imm);
extern ssize_t mips_emit_addiu(mips_insn_t* insn, const mips_reg_t rd, const mips_reg_t rs, const mips_imm_t imm);
extern ssize_t mips_emit_sub(mips_insn_t* insn, const mips_reg_t rd, const mips_reg_t rs, const mips_reg_t rt);
extern ssize_t mips_emit_subu(mips_insn_t* insn, const mips_reg_t rd, const mips_reg_t rs, const mips_reg_t rt);
extern ssize_t mips_emit_mult(mips_insn_t* insn, const mips_reg_t rs, const mips_reg_t rt);
extern ssize_t mips_emit_multu(mips_insn_t* insn, const mips_reg_t rs, const mips_reg_t rt);
extern ssize_t mips_emit_mul(mips_insn_t* insn, const mips_reg_t rd, const mips_reg_t rs, const mips_reg_t rt);
extern ssize_t mips_emit_div(mips_insn_t* insn, const mips_reg_t rs, const mips_reg_t rt);
extern ssize_t mips_emit_divu(mips_insn_t* insn, const mips_reg_t rs, const mips_reg_t rt);
extern ssize_t mips_emit_and(mips_insn_t* insn, const mips_reg_t rd, const mips_reg_t rs, const mips_reg_t rt);
extern ssize_t mips_emit_or(mips_insn_t* insn, const mips_reg_t rd, const mips_reg_t rs, const mips_reg_t rt);
extern ssize_t mips_emit_xor(mips_insn_t* insn, const mips_reg_t rd, const mips_reg_t rs, const mips_reg_t rt);
extern ssize_t mips_emit_nor(mips_insn_t* insn, const mips_reg_t rd, const mips_reg_t rs, const mips_reg_t rt);
extern ssize_t mips_emit_j(mips_insn_t* insn, const mips_addr_t target);
extern ssize_t mips_emit_jal(mips_insn_t* insn, const mips_addr_t target);

#ifdef __cplusplus
}
#endif

#endif /* _MACHINERY_MIPS_H */
