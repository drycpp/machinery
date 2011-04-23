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

ssize_t
x86_emit_nop(x86_insn_t* insn) {
  return x86_encode_1b_insn(insn, 0x90);
}
