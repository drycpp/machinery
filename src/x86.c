/* This is free and unencumbered software released into the public domain. */

#include "x86.h"
#include "config.h"
#include <assert.h>
#include <errno.h>

static ssize_t
x86_encode_1b_insn(x86_insn_t* insn, const x86_opcode_t opcode) {
  if (insn == NULL)
    return -(errno = EINVAL); // invalid argument

  insn->opcode = opcode;

  return 1;
}

static ssize_t
x86_encode_2b_insn(x86_insn_t* insn, const x86_opcode_t opcode, const x86_opcode_t opcode2) {
  if (insn == NULL)
    return -(errno = EINVAL); // invalid argument

  insn->opcode  = opcode;
  insn->opcode2 = opcode2;

  return 2;
}

static ssize_t
x86_encode_3b_insn(x86_insn_t* insn, const x86_opcode_t opcode, const x86_opcode_t opcode2, const x86_opcode_t opcode3) {
  if (insn == NULL)
    return -(errno = EINVAL); // invalid argument

  insn->opcode  = opcode;
  insn->opcode2 = opcode2;
  insn->opcode3 = opcode3;

  return 3;
}

/* General-purpose instructions */

ssize_t
x86_emit_aaa(x86_insn_t* insn) {
  return x86_encode_1b_insn(insn, 0x37);
}

ssize_t
x86_emit_aas(x86_insn_t* insn) {
  return x86_encode_1b_insn(insn, 0x3F);
}

ssize_t
x86_emit_cbw(x86_insn_t* insn) {
  return x86_encode_1b_insn(insn, 0x98);
}

ssize_t
x86_emit_cwde(x86_insn_t* insn) {
  return x86_encode_1b_insn(insn, 0x98);
}

ssize_t
x86_emit_cdqe(x86_insn_t* insn) {
  return x86_encode_1b_insn(insn, 0x98);
}

ssize_t
x86_emit_cwd(x86_insn_t* insn) {
  return x86_encode_1b_insn(insn, 0x99);
}

ssize_t
x86_emit_cdq(x86_insn_t* insn) {
  return x86_encode_1b_insn(insn, 0x99);
}

ssize_t
x86_emit_cqo(x86_insn_t* insn) {
  return x86_encode_1b_insn(insn, 0x99);
}

ssize_t
x86_emit_clc(x86_insn_t* insn) {
  return x86_encode_1b_insn(insn, 0xF8);
}

ssize_t
x86_emit_cld(x86_insn_t* insn) {
  return x86_encode_1b_insn(insn, 0xFC);
}

ssize_t
x86_emit_cmc(x86_insn_t* insn) {
  return x86_encode_1b_insn(insn, 0xF5);
}

ssize_t
x86_emit_cmpsb(x86_insn_t* insn) {
  return x86_encode_1b_insn(insn, 0xA6);
}

ssize_t
x86_emit_cmpsw(x86_insn_t* insn) {
  return x86_encode_1b_insn(insn, 0xA7);
}

ssize_t
x86_emit_cmpsd(x86_insn_t* insn) {
  return x86_encode_1b_insn(insn, 0xA7);
}

ssize_t
x86_emit_cmpsq(x86_insn_t* insn) {
  return x86_encode_1b_insn(insn, 0xA7);
}

ssize_t
x86_emit_daa(x86_insn_t* insn) {
  return x86_encode_1b_insn(insn, 0x27);
}

ssize_t
x86_emit_das(x86_insn_t* insn) {
  return x86_encode_1b_insn(insn, 0x2F);
}

ssize_t
x86_emit_insb(x86_insn_t* insn) {
  return x86_encode_1b_insn(insn, 0x6C);
}

ssize_t
x86_emit_insw(x86_insn_t* insn) {
  return x86_encode_1b_insn(insn, 0x6D);
}

ssize_t
x86_emit_insd(x86_insn_t* insn) {
  return x86_encode_1b_insn(insn, 0x6D);
}

ssize_t
x86_emit_into(x86_insn_t* insn) {
  return x86_encode_1b_insn(insn, 0xCE);
}

ssize_t
x86_emit_lahf(x86_insn_t* insn) {
  return x86_encode_1b_insn(insn, 0x9F);
}

ssize_t
x86_emit_leave(x86_insn_t* insn) {
  return x86_encode_1b_insn(insn, 0xC9);
}

ssize_t
x86_emit_lodsb(x86_insn_t* insn) {
  return x86_encode_1b_insn(insn, 0xAC);
}

ssize_t
x86_emit_lodsw(x86_insn_t* insn) {
  return x86_encode_1b_insn(insn, 0xAD);
}

ssize_t
x86_emit_lodsd(x86_insn_t* insn) {
  return x86_encode_1b_insn(insn, 0xAD);
}

ssize_t
x86_emit_lodsq(x86_insn_t* insn) {
  return x86_encode_1b_insn(insn, 0xAD);
}

ssize_t
x86_emit_movsb(x86_insn_t* insn) {
  return x86_encode_1b_insn(insn, 0xA4);
}

ssize_t
x86_emit_movsw(x86_insn_t* insn) {
  return x86_encode_1b_insn(insn, 0xA5);
}

ssize_t
x86_emit_movsd(x86_insn_t* insn) {
  return x86_encode_1b_insn(insn, 0xA5);
}

ssize_t
x86_emit_movsq(x86_insn_t* insn) {
  return x86_encode_1b_insn(insn, 0xA5);
}

ssize_t
x86_emit_nop(x86_insn_t* insn) {
  return x86_encode_1b_insn(insn, 0x90);
}

ssize_t
x86_emit_outsb(x86_insn_t* insn) {
  return x86_encode_1b_insn(insn, 0x6E);
}

ssize_t
x86_emit_outsw(x86_insn_t* insn) {
  return x86_encode_1b_insn(insn, 0x6F);
}

ssize_t
x86_emit_outsd(x86_insn_t* insn) {
  return x86_encode_1b_insn(insn, 0x6F);
}

ssize_t
x86_emit_popa(x86_insn_t* insn) {
  return x86_encode_1b_insn(insn, 0x61);
}

ssize_t
x86_emit_popad(x86_insn_t* insn) {
  return x86_encode_1b_insn(insn, 0x61);
}

ssize_t
x86_emit_popf(x86_insn_t* insn) {
  return x86_encode_1b_insn(insn, 0x9D);
}

ssize_t
x86_emit_popfd(x86_insn_t* insn) {
  return x86_encode_1b_insn(insn, 0x9D);
}

ssize_t
x86_emit_popfq(x86_insn_t* insn) {
  return x86_encode_1b_insn(insn, 0x9D);
}

ssize_t
x86_emit_pusha(x86_insn_t* insn) {
  return x86_encode_1b_insn(insn, 0x60);
}

ssize_t
x86_emit_pushad(x86_insn_t* insn) {
  return x86_encode_1b_insn(insn, 0x60);
}

ssize_t
x86_emit_pushf(x86_insn_t* insn) {
  return x86_encode_1b_insn(insn, 0x9C);
}

ssize_t
x86_emit_pushfd(x86_insn_t* insn) {
  return x86_encode_1b_insn(insn, 0x9C);
}

ssize_t
x86_emit_pushfq(x86_insn_t* insn) {
  return x86_encode_1b_insn(insn, 0x9C);
}

ssize_t
x86_emit_ret(x86_insn_t* insn) {
  return x86_encode_1b_insn(insn, 0xC3);
}

ssize_t
x86_emit_retf(x86_insn_t* insn) {
  return x86_encode_1b_insn(insn, 0xCB);
}

ssize_t
x86_emit_sahf(x86_insn_t* insn) {
  return x86_encode_1b_insn(insn, 0x9E);
}

ssize_t
x86_emit_scasb(x86_insn_t* insn) {
  return x86_encode_1b_insn(insn, 0xAE);
}

ssize_t
x86_emit_scasw(x86_insn_t* insn) {
  return x86_encode_1b_insn(insn, 0xAF);
}

ssize_t
x86_emit_scasd(x86_insn_t* insn) {
  return x86_encode_1b_insn(insn, 0xAF);
}

ssize_t
x86_emit_scasq(x86_insn_t* insn) {
  return x86_encode_1b_insn(insn, 0xAF);
}

ssize_t
x86_emit_stc(x86_insn_t* insn) {
  return x86_encode_1b_insn(insn, 0xF9);
}

ssize_t
x86_emit_std(x86_insn_t* insn) {
  return x86_encode_1b_insn(insn, 0xFD);
}

ssize_t
x86_emit_stosb(x86_insn_t* insn) {
  return x86_encode_1b_insn(insn, 0xAA);
}

ssize_t
x86_emit_stosw(x86_insn_t* insn) {
  return x86_encode_1b_insn(insn, 0xAB);
}

ssize_t
x86_emit_stosd(x86_insn_t* insn) {
  return x86_encode_1b_insn(insn, 0xAB);
}

ssize_t
x86_emit_stosq(x86_insn_t* insn) {
  return x86_encode_1b_insn(insn, 0xAB);
}

ssize_t
x86_emit_xlatb(x86_insn_t* insn) {
  return x86_encode_1b_insn(insn, 0xD7);
}

/* System instructions */

ssize_t
x86_emit_clgi(x86_insn_t* insn) {
  return x86_encode_3b_insn(insn, 0x0F, 0x01, 0xDD);
}

ssize_t
x86_emit_cli(x86_insn_t* insn) {
  return x86_encode_1b_insn(insn, 0xFA);
}

ssize_t
x86_emit_clts(x86_insn_t* insn) {
  return x86_encode_2b_insn(insn, 0x0F, 0x06);
}

ssize_t
x86_emit_hlt(x86_insn_t* insn) {
  return x86_encode_1b_insn(insn, 0xF4);
}

ssize_t
x86_emit_int3(x86_insn_t* insn) {
  return x86_encode_1b_insn(insn, 0xCC);
}

ssize_t
x86_emit_invd(x86_insn_t* insn) {
  return x86_encode_2b_insn(insn, 0x0F, 0x08);
}

ssize_t
x86_emit_invlpga(x86_insn_t* insn) {
  return x86_encode_3b_insn(insn, 0x0F, 0x01, 0xDF);
}

ssize_t
x86_emit_iret(x86_insn_t* insn) {
  return x86_encode_1b_insn(insn, 0xCF);
}

ssize_t
x86_emit_iretd(x86_insn_t* insn) {
  return x86_encode_1b_insn(insn, 0xCF);
}

ssize_t
x86_emit_iretq(x86_insn_t* insn) {
  return x86_encode_1b_insn(insn, 0xCF);
}

ssize_t
x86_emit_monitor(x86_insn_t* insn) {
  return x86_encode_3b_insn(insn, 0x0F, 0x01, 0xC8);
}

ssize_t
x86_emit_mwait(x86_insn_t* insn) {
  return x86_encode_3b_insn(insn, 0x0F, 0x01, 0xC9);
}

ssize_t
x86_emit_rdmsr(x86_insn_t* insn) {
  return x86_encode_2b_insn(insn, 0x0F, 0x32);
}

ssize_t
x86_emit_rdpmc(x86_insn_t* insn) {
  return x86_encode_2b_insn(insn, 0x0F, 0x33);
}

ssize_t
x86_emit_rdtsc(x86_insn_t* insn) {
  return x86_encode_2b_insn(insn, 0x0F, 0x31);
}

ssize_t
x86_emit_rdtscp(x86_insn_t* insn) {
  return x86_encode_3b_insn(insn, 0x0F, 0x01, 0xF9);
}

ssize_t
x86_emit_rsm(x86_insn_t* insn) {
  return x86_encode_2b_insn(insn, 0x0F, 0xAA);
}

ssize_t
x86_emit_skinit(x86_insn_t* insn) {
  return x86_encode_3b_insn(insn, 0x0F, 0x01, 0xDE);
}

ssize_t
x86_emit_sti(x86_insn_t* insn) {
  return x86_encode_1b_insn(insn, 0xFB);
}

ssize_t
x86_emit_stgi(x86_insn_t* insn) {
  return x86_encode_3b_insn(insn, 0x0F, 0x01, 0xDC);
}

ssize_t
x86_emit_swapgs(x86_insn_t* insn) {
  return x86_encode_3b_insn(insn, 0x0F, 0x01, 0xF8);
}

ssize_t
x86_emit_syscall(x86_insn_t* insn) {
  return x86_encode_2b_insn(insn, 0x0F, 0x05);
}

ssize_t
x86_emit_sysenter(x86_insn_t* insn) {
  return x86_encode_2b_insn(insn, 0x0F, 0x34);
}

ssize_t
x86_emit_sysexit(x86_insn_t* insn) {
  return x86_encode_2b_insn(insn, 0x0F, 0x35);
}

ssize_t
x86_emit_sysret(x86_insn_t* insn) {
  return x86_encode_2b_insn(insn, 0x0F, 0x07);
}

ssize_t
x86_emit_ud2(x86_insn_t* insn) {
  return x86_encode_2b_insn(insn, 0x0F, 0x0B);
}

ssize_t
x86_emit_vmload(x86_insn_t* insn) {
  return x86_encode_3b_insn(insn, 0x0F, 0x01, 0xDA);
}

ssize_t
x86_emit_vmmcall(x86_insn_t* insn) {
  return x86_encode_3b_insn(insn, 0x0F, 0x01, 0xD9);
}

ssize_t
x86_emit_vmrun(x86_insn_t* insn) {
  return x86_encode_3b_insn(insn, 0x0F, 0x01, 0xD8);
}

ssize_t
x86_emit_vmsave(x86_insn_t* insn) {
  return x86_encode_3b_insn(insn, 0x0F, 0x01, 0xDB);
}

ssize_t
x86_emit_wbinvd(x86_insn_t* insn) {
  return x86_encode_2b_insn(insn, 0x0F, 0x09);
}

ssize_t
x86_emit_wrmsr(x86_insn_t* insn) {
  return x86_encode_2b_insn(insn, 0x0F, 0x30);
}
