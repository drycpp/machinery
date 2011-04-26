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

/* x86 general-purpose registers (8-bit) */
typedef enum {
  X86_REG_AL = 0,  /* 0b000 */
  X86_REG_CL,      /* 0b001 */
  X86_REG_DL,      /* 0b010 */
  X86_REG_BL,      /* 0b011 */
  X86_REG_AH,      /* 0b100 */
  X86_REG_CH,      /* 0b101 */
  X86_REG_DH,      /* 0b110 */
  X86_REG_BH,      /* 0b111 */
} x86_reg8_t;

/* x86 general-purpose registers (16-bit) */
typedef enum {
  X86_REG_AX = 0,  /* 0b000 */
  X86_REG_CX,      /* 0b001 */
  X86_REG_DX,      /* 0b010 */
  X86_REG_BX,      /* 0b011 */
  X86_REG_SP,      /* 0b100 */
  X86_REG_BP,      /* 0b101 */
  X86_REG_SI,      /* 0b110 */
  X86_REG_DI,      /* 0b111 */
} x86_reg16_t;

/* x86 general-purpose registers (32-bit) */
typedef enum {
  X86_REG_EAX = 0, /* 0b000 */
  X86_REG_ECX,     /* 0b001 */
  X86_REG_EDX,     /* 0b010 */
  X86_REG_EBX,     /* 0b011 */
  X86_REG_ESP,     /* 0b100 */
  X86_REG_EBP,     /* 0b101 */
  X86_REG_ESI,     /* 0b110 */
  X86_REG_EDI,     /* 0b111 */
} x86_reg32_t;

/* x86 general-purpose registers (64-bit) */
typedef enum {
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
} x86_reg32_t;

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
typedef int64_t x86_disp64_t;
typedef union {
  x86_disp8_t  b;
  x86_disp16_t w;
  x86_disp32_t d;
  x86_disp64_t q;
} x86_disp_t;

/* x86 immediate operands */
typedef int8_t  x86_imm8_t;
typedef int16_t x86_imm16_t;
typedef int32_t x86_imm32_t;
typedef int64_t x86_imm64_t;

/* x86 instruction formats */
typedef union {
  x86_opcode_t opcode;
  x86_opcode_t opcode2;
  x86_opcode_t opcode3;
} x86_insn_t;

/* x86 instruction emitters (general-purpose instructions) */
extern ssize_t x86_emit_aaa(x86_insn_t* insn);
extern ssize_t x86_emit_aas(x86_insn_t* insn);
extern ssize_t x86_emit_cbw(x86_insn_t* insn);
extern ssize_t x86_emit_cwde(x86_insn_t* insn);
extern ssize_t x86_emit_cdqe(x86_insn_t* insn);
extern ssize_t x86_emit_cwd(x86_insn_t* insn);
extern ssize_t x86_emit_cdq(x86_insn_t* insn);
extern ssize_t x86_emit_cqo(x86_insn_t* insn);
extern ssize_t x86_emit_clc(x86_insn_t* insn);
extern ssize_t x86_emit_cld(x86_insn_t* insn);
extern ssize_t x86_emit_cmc(x86_insn_t* insn);
extern ssize_t x86_emit_cmpsb(x86_insn_t* insn);
extern ssize_t x86_emit_cmpsw(x86_insn_t* insn);
extern ssize_t x86_emit_cmpsd(x86_insn_t* insn);
extern ssize_t x86_emit_cmpsq(x86_insn_t* insn);
extern ssize_t x86_emit_daa(x86_insn_t* insn);
extern ssize_t x86_emit_das(x86_insn_t* insn);
extern ssize_t x86_emit_insb(x86_insn_t* insn);
extern ssize_t x86_emit_insw(x86_insn_t* insn);
extern ssize_t x86_emit_insd(x86_insn_t* insn);
extern ssize_t x86_emit_into(x86_insn_t* insn);
extern ssize_t x86_emit_lahf(x86_insn_t* insn);
extern ssize_t x86_emit_leave(x86_insn_t* insn);
extern ssize_t x86_emit_lodsb(x86_insn_t* insn);
extern ssize_t x86_emit_lodsw(x86_insn_t* insn);
extern ssize_t x86_emit_lodsd(x86_insn_t* insn);
extern ssize_t x86_emit_lodsq(x86_insn_t* insn);
extern ssize_t x86_emit_movsb(x86_insn_t* insn);
extern ssize_t x86_emit_movsw(x86_insn_t* insn);
extern ssize_t x86_emit_movsd(x86_insn_t* insn);
extern ssize_t x86_emit_movsq(x86_insn_t* insn);
extern ssize_t x86_emit_nop(x86_insn_t* insn);
extern ssize_t x86_emit_outsb(x86_insn_t* insn);
extern ssize_t x86_emit_outsw(x86_insn_t* insn);
extern ssize_t x86_emit_outsd(x86_insn_t* insn);
extern ssize_t x86_emit_popa(x86_insn_t* insn);
extern ssize_t x86_emit_popad(x86_insn_t* insn);
extern ssize_t x86_emit_popf(x86_insn_t* insn);
extern ssize_t x86_emit_popfd(x86_insn_t* insn);
extern ssize_t x86_emit_popfq(x86_insn_t* insn);
extern ssize_t x86_emit_pusha(x86_insn_t* insn);
extern ssize_t x86_emit_pushad(x86_insn_t* insn);
extern ssize_t x86_emit_pushf(x86_insn_t* insn);
extern ssize_t x86_emit_pushfd(x86_insn_t* insn);
extern ssize_t x86_emit_pushfq(x86_insn_t* insn);
extern ssize_t x86_emit_ret(x86_insn_t* insn);
extern ssize_t x86_emit_retf(x86_insn_t* insn);
extern ssize_t x86_emit_sahf(x86_insn_t* insn);
extern ssize_t x86_emit_scasb(x86_insn_t* insn);
extern ssize_t x86_emit_scasw(x86_insn_t* insn);
extern ssize_t x86_emit_scasd(x86_insn_t* insn);
extern ssize_t x86_emit_scasq(x86_insn_t* insn);
extern ssize_t x86_emit_stc(x86_insn_t* insn);
extern ssize_t x86_emit_std(x86_insn_t* insn);
extern ssize_t x86_emit_stosb(x86_insn_t* insn);
extern ssize_t x86_emit_stosw(x86_insn_t* insn);
extern ssize_t x86_emit_stosd(x86_insn_t* insn);
extern ssize_t x86_emit_stosq(x86_insn_t* insn);
extern ssize_t x86_emit_xlatb(x86_insn_t* insn);

/* x86 instruction emitters (system instructions) */
extern ssize_t x86_emit_clgi(x86_insn_t* insn);
extern ssize_t x86_emit_cli(x86_insn_t* insn);
extern ssize_t x86_emit_clts(x86_insn_t* insn);
extern ssize_t x86_emit_hlt(x86_insn_t* insn);
extern ssize_t x86_emit_int3(x86_insn_t* insn);
extern ssize_t x86_emit_invd(x86_insn_t* insn);
extern ssize_t x86_emit_invlpga(x86_insn_t* insn);
extern ssize_t x86_emit_iret(x86_insn_t* insn);
extern ssize_t x86_emit_iretd(x86_insn_t* insn);
extern ssize_t x86_emit_iretq(x86_insn_t* insn);
extern ssize_t x86_emit_monitor(x86_insn_t* insn);
extern ssize_t x86_emit_mwait(x86_insn_t* insn);
extern ssize_t x86_emit_rdmsr(x86_insn_t* insn);
extern ssize_t x86_emit_rdpmc(x86_insn_t* insn);
extern ssize_t x86_emit_rdtsc(x86_insn_t* insn);
extern ssize_t x86_emit_rdtscp(x86_insn_t* insn);
extern ssize_t x86_emit_rsm(x86_insn_t* insn);
extern ssize_t x86_emit_skinit(x86_insn_t* insn);
extern ssize_t x86_emit_sti(x86_insn_t* insn);
extern ssize_t x86_emit_stgi(x86_insn_t* insn);
extern ssize_t x86_emit_swapgs(x86_insn_t* insn);
extern ssize_t x86_emit_syscall(x86_insn_t* insn);
extern ssize_t x86_emit_sysenter(x86_insn_t* insn);
extern ssize_t x86_emit_sysexit(x86_insn_t* insn);
extern ssize_t x86_emit_sysret(x86_insn_t* insn);
extern ssize_t x86_emit_ud2(x86_insn_t* insn);
extern ssize_t x86_emit_vmload(x86_insn_t* insn);
extern ssize_t x86_emit_vmmcall(x86_insn_t* insn);
extern ssize_t x86_emit_vmrun(x86_insn_t* insn);
extern ssize_t x86_emit_vmsave(x86_insn_t* insn);
extern ssize_t x86_emit_wbinvd(x86_insn_t* insn);
extern ssize_t x86_emit_wrmsr(x86_insn_t* insn);

#ifdef __cplusplus
}
#endif

#endif /* _MACHINERY_X86_H */
