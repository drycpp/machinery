/* This is free and unencumbered software released into the public domain. */

#ifndef MACHINERY_ARCH_X86_EMITTER_H
#define MACHINERY_ARCH_X86_EMITTER_H

/**
 * @file
 *
 * x86 machine code emission.
 */

#include "encoding.h"

#include <cstddef> /* for std::size_t */
#include <cstdint> /* for std::uint8_t */
#include <vector>  /* for std::vector */

namespace machinery {
  namespace arch {
    class x86_emitter;
  }
}

/**
 * x86 machine code emitter.
 *
 * @note Instances of this class are movable, but not copyable.
 */
class machinery::arch::x86_emitter {
  std::vector<std::uint8_t>& _buffer;
  std::size_t _buffer_start;

public:
  /**
   * Default constructor.
   */
  x86_emitter() noexcept = delete;

  /**
   * Constructor.
   *
   * @param buffer the output buffer
   */
  x86_emitter(std::vector<std::uint8_t>& buffer) noexcept
    : _buffer(buffer),
      _buffer_start(buffer.size()) {}

  /**
   * Copy constructor.
   */
  x86_emitter(const x86_emitter& other) noexcept = delete;

  /**
   * Move constructor.
   */
  x86_emitter(x86_emitter&& other) noexcept = default;

  /**
   * Destructor.
   */
  ~x86_emitter() noexcept = default;

  /**
   * Copy assignment operator.
   */
  x86_emitter& operator=(const x86_emitter& other) noexcept = delete;

  /**
   * Move assignment operator.
   */
  x86_emitter& operator=(x86_emitter&& other) noexcept = default;

  /**
   * Returns the current buffer offset as a byte count.
   *
   * This indicates how many bytes have been written into the buffer by this
   * emitter instance.
   *
   * @return a zero-based byte offset
   */
  std::size_t offset() const noexcept {
    return _buffer.size() - _buffer_start;
  }

  /**
   * Emits a one-byte instruction.
   *
   * @param opcode the opcode byte
   * @return `*this`
   * @throws std::bad_alloc if out of memory
   */
  inline x86_emitter& emit(const x86_opcode opcode) {
    _buffer.emplace_back(opcode);
    return *this;
  }

  /**
   * Emits a two-byte instruction.
   *
   * @param opcode  the first opcode byte
   * @param opcode2 the second opcode byte
   * @return `*this`
   * @throws std::bad_alloc if out of memory
   */
  inline x86_emitter& emit(const x86_opcode opcode,
                           const x86_opcode opcode2) {
    _buffer.insert(_buffer.end(), {opcode, opcode2});
    return *this;
  }

  /**
   * Emits a three-byte instruction.
   *
   * @param opcode  the first opcode byte
   * @param opcode2 the second opcode byte
   * @param opcode3 the third opcode byte
   * @return `*this`
   * @throws std::bad_alloc if out of memory
   */
  inline x86_emitter& emit(const x86_opcode opcode,
                           const x86_opcode opcode2,
                           const x86_opcode opcode3) {
    _buffer.insert(_buffer.end(), {opcode, opcode2, opcode3});
    return *this;
  }

  /**
   * @class emit_immediate_value
   *
   * @param imm the immediate value
   * @return `*this`
   * @throws std::bad_alloc if out of memory
   */

  /**
   * Emits an 8-bit immediate value.
   *
   * @copydetails emit_immediate_value
   */
  inline x86_emitter& emit(const x86_imm8 imm) {
    _buffer.emplace_back(imm.u8);
    return *this;
  }

  /**
   * Emits a 16-bit immediate value.
   *
   * @copydetails emit_immediate_value
   */
  inline x86_emitter& emit(const x86_imm16 imm) {
    _buffer.insert(_buffer.end(), {imm.u8[0], imm.u8[1]});
    return *this;
  }

  /**
   * Emits a 32-bit immediate value.
   *
   * @copydetails emit_immediate_value
   */
  inline x86_emitter& emit(const x86_imm32 imm) {
    _buffer.insert(_buffer.end(), {
      imm.u8[0], imm.u8[1], imm.u8[2], imm.u8[3]
    });
    return *this;
  }

  /**
   * Emits a 64-bit immediate value.
   *
   * @copydetails emit_immediate_value
   */
  inline x86_emitter& emit(const x86_imm64 imm) {
    _buffer.insert(_buffer.end(), {
      imm.u8[0], imm.u8[1], imm.u8[2], imm.u8[3],
      imm.u8[4], imm.u8[5], imm.u8[6], imm.u8[7]
    });
    return *this;
  }

  /**
   * @name General-Purpose Instructions
   *
   * These instructions operate on the general-purpose (GP) registers and
   * can be used at all privilege levels.
   */

  /**@{*/

  /**
   * @class emit_general_purpose_instruction
   *
   * @return `*this`
   * @throws std::bad_alloc if out of memory
   */

  /**
   * Emits a one-byte `AAA` instruction.
   *
   * @copydetails emit_general_purpose_instruction
   */
  x86_emitter& emit_aaa() {
    return emit(0x37);
  }

  /**
   * Emits a one-byte `AAS` instruction.
   *
   * @copydetails emit_general_purpose_instruction
   */
  x86_emitter& emit_aas() {
    return emit(0x3F);
  }

  /**
   * Emits a one-byte `CBW` instruction.
   *
   * @copydetails emit_general_purpose_instruction
   */
  x86_emitter& emit_cbw() {
    return emit(0x98);
  }

  /**
   * Emits a one-byte `CWDE` instruction.
   *
   * @copydetails emit_general_purpose_instruction
   */
  x86_emitter& emit_cwde() {
    return emit(0x98);
  }

  /**
   * Emits a one-byte `CDQE` instruction.
   *
   * @copydetails emit_general_purpose_instruction
   */
  x86_emitter& emit_cdqe() {
    return emit(0x98);
  }

  /**
   * Emits a one-byte `CWD` instruction.
   *
   * @copydetails emit_general_purpose_instruction
   */
  x86_emitter& emit_cwd() {
    return emit(0x99);
  }

  /**
   * Emits a one-byte `CDQ` instruction.
   *
   * @copydetails emit_general_purpose_instruction
   */
  x86_emitter& emit_cdq() {
    return emit(0x99);
  }

  /**
   * Emits a one-byte `CQO` instruction.
   *
   * @copydetails emit_general_purpose_instruction
   */
  x86_emitter& emit_cqo() {
    return emit(0x99);
  }

  /**
   * Emits a one-byte `CLC` instruction.
   *
   * @copydetails emit_general_purpose_instruction
   */
  x86_emitter& emit_clc() {
    return emit(0xF8);
  }

  /**
   * Emits a one-byte `CLD` instruction.
   *
   * @copydetails emit_general_purpose_instruction
   */
  x86_emitter& emit_cld() {
    return emit(0xFC);
  }

  /**
   * Emits a one-byte `CMC` instruction.
   *
   * @copydetails emit_general_purpose_instruction
   */
  x86_emitter& emit_cmc() {
    return emit(0xF5);
  }

  /**
   * Emits a one-byte `CMPSB` instruction.
   *
   * @copydetails emit_general_purpose_instruction
   */
  x86_emitter& emit_cmpsb() {
    return emit(0xA6);
  }

  /**
   * Emits a one-byte `CMPSW` instruction.
   *
   * @copydetails emit_general_purpose_instruction
   */
  x86_emitter& emit_cmpsw() {
    return emit(0xA7);
  }

  /**
   * Emits a one-byte `CMPSD` instruction.
   *
   * @copydetails emit_general_purpose_instruction
   */
  x86_emitter& emit_cmpsd() {
    return emit(0xA7);
  }

  /**
   * Emits a one-byte `CMPSQ` instruction.
   *
   * @copydetails emit_general_purpose_instruction
   */
  x86_emitter& emit_cmpsq() {
    return emit(0xA7);
  }

  /**
   * Emits a one-byte `DAA` instruction.
   *
   * @copydetails emit_general_purpose_instruction
   */
  x86_emitter& emit_daa() {
    return emit(0x27);
  }

  /**
   * Emits a one-byte `DAS` instruction.
   *
   * @copydetails emit_general_purpose_instruction
   */
  x86_emitter& emit_das() {
    return emit(0x2F);
  }

  /**
   * Emits a one-byte `INSB` instruction.
   *
   * @copydetails emit_general_purpose_instruction
   */
  x86_emitter& emit_insb() {
    return emit(0x6C);
  }

  /**
   * Emits a one-byte `INSW` instruction.
   *
   * @copydetails emit_general_purpose_instruction
   */
  x86_emitter& emit_insw() {
    return emit(0x6D);
  }

  /**
   * Emits a one-byte `INSD` instruction.
   *
   * @copydetails emit_general_purpose_instruction
   */
  x86_emitter& emit_insd() {
    return emit(0x6D);
  }

  /**
   * Emits a one-byte `INTO` instruction.
   *
   * @copydetails emit_general_purpose_instruction
   */
  x86_emitter& emit_into() {
    return emit(0xCE);
  }

  /**
   * Emits a one-byte `LAHF` instruction.
   *
   * @copydetails emit_general_purpose_instruction
   */
  x86_emitter& emit_lahf() {
    return emit(0x9F);
  }

  /**
   * Emits a one-byte `LEAVE` instruction.
   *
   * @copydetails emit_general_purpose_instruction
   */
  x86_emitter& emit_leave() {
    return emit(0xC9);
  }

  /**
   * Emits a one-byte `LODSB` instruction.
   *
   * @copydetails emit_general_purpose_instruction
   */
  x86_emitter& emit_lodsb() {
    return emit(0xAC);
  }

  /**
   * Emits a one-byte `LODSW` instruction.
   *
   * @copydetails emit_general_purpose_instruction
   */
  x86_emitter& emit_lodsw() {
    return emit(0xAD);
  }

  /**
   * Emits a one-byte `LODSD` instruction.
   *
   * @copydetails emit_general_purpose_instruction
   */
  x86_emitter& emit_lodsd() {
    return emit(0xAD);
  }

  /**
   * Emits a one-byte `LODSQ` instruction.
   *
   * @copydetails emit_general_purpose_instruction
   */
  x86_emitter& emit_lodsq() {
    return emit(0xAD);
  }

  /**
   * Emits a two-byte `MOV reg8, imm8` instruction.
   *
   * @param reg the 8-bit target register operand
   * @param imm the 8-bit immediate value operand
   * @todo Implement this method.
   * @copydetails emit_general_purpose_instruction
   */
  x86_emitter& emit_mov(const x86_reg8 reg,
                        const x86_imm8 imm) {
    return emit(0xB0 + static_cast<std::uint8_t>(reg)).emit(imm);
  }

  /**
   * Emits a three-byte `MOV reg16, imm16` instruction.
   *
   * @param reg the 16-bit target register operand
   * @param imm the 16-bit immediate value operand
   * @todo Implement this method.
   * @copydetails emit_general_purpose_instruction
   */
  x86_emitter& emit_mov(const x86_reg16 reg,
                        const x86_imm16 imm) {
    return emit(0xB8 + static_cast<std::uint8_t>(reg)).emit(imm);
  }

  /**
   * Emits a five-byte `MOV reg32, imm32` instruction.
   *
   * @param reg the 32-bit target register operand
   * @param imm the 32-bit immediate value operand
   * @todo Implement this method.
   * @copydetails emit_general_purpose_instruction
   */
  x86_emitter& emit_mov(const x86_reg32 reg,
                        const x86_imm32 imm) {
    return emit(0xB8 + static_cast<std::uint8_t>(reg)).emit(imm);
  }

  /**
   * Emits a nine or ten-byte `MOV reg64, imm64` instruction.
   *
   * @param reg the 64-bit target register operand
   * @param imm the 64-bit immediate value operand
   * @todo Implement this method.
   * @copydetails emit_general_purpose_instruction
   */
  x86_emitter& emit_mov(const x86_reg64 reg,
                        const x86_imm64 imm) {
    //assert(reg < x86_reg64::R8); // FIXME
    return emit(0xB8 + static_cast<std::uint8_t>(reg)).emit(imm);
  }

  /**
   * Emits a one-byte `MOVSB` instruction.
   *
   * @copydetails emit_general_purpose_instruction
   */
  x86_emitter& emit_movsb() {
    return emit(0xA4);
  }

  /**
   * Emits a one-byte `MOVSW` instruction.
   *
   * @copydetails emit_general_purpose_instruction
   */
  x86_emitter& emit_movsw() {
    return emit(0xA5);
  }

  /**
   * Emits a one-byte `MOVSD` instruction.
   *
   * @copydetails emit_general_purpose_instruction
   */
  x86_emitter& emit_movsd() {
    return emit(0xA5);
  }

  /**
   * Emits a one-byte `MOVSQ` instruction.
   *
   * @copydetails emit_general_purpose_instruction
   */
  x86_emitter& emit_movsq() {
    return emit(0xA5);
  }

  /**
   * Emits a ?-byte `MUL reg8` instruction.
   *
   * @param reg8 an 8-bit register operand
   * @todo Implement this method.
   * @copydetails emit_general_purpose_instruction
   */
  x86_emitter& emit_mul(const x86_reg8 reg) {
    return (void)reg, *this; // TODO
  }

  /**
   * Emits a ?-byte `MUL reg16` instruction.
   *
   * @param reg a 16-bit register operand
   * @todo Implement this method.
   * @copydetails emit_general_purpose_instruction
   */
  x86_emitter& emit_mul(const x86_reg16 reg) {
    return (void)reg, *this; // TODO
  }

  /**
   * Emits a ?-byte `MUL reg32` instruction.
   *
   * @param reg a 32-bit register operand
   * @todo Implement this method.
   * @copydetails emit_general_purpose_instruction
   */
  x86_emitter& emit_mul(const x86_reg32 reg) {
    return (void)reg, *this; // TODO
  }

  /**
   * Emits a ?-byte `MUL reg32` instruction.
   *
   * @param reg a 64-bit register operand
   * @todo Implement this method.
   * @copydetails emit_general_purpose_instruction
   */
  x86_emitter& emit_mul(const x86_reg64 reg) {
    return (void)reg, *this; // TODO
  }

  /**
   * Emits a one-byte `NOP` instruction.
   *
   * @copydetails emit_general_purpose_instruction
   */
  x86_emitter& emit_nop() {
    return emit(0x90);
  }

  /**
   * Emits a one-byte `OUTSB` instruction.
   *
   * @copydetails emit_general_purpose_instruction
   */
  x86_emitter& emit_outsb() {
    return emit(0x6E);
  }

  /**
   * Emits a one-byte `OUTSW` instruction.
   *
   * @copydetails emit_general_purpose_instruction
   */
  x86_emitter& emit_outsw() {
    return emit(0x6F);
  }

  /**
   * Emits a one-byte `OUTSD` instruction.
   *
   * @copydetails emit_general_purpose_instruction
   */
  x86_emitter& emit_outsd() {
    return emit(0x6F);
  }

  /**
   * Emits a one-byte `POPA` instruction.
   *
   * @copydetails emit_general_purpose_instruction
   */
  x86_emitter& emit_popa() {
    return emit(0x61);
  }

  /**
   * Emits a one-byte `POPAD` instruction.
   *
   * @copydetails emit_general_purpose_instruction
   */
  x86_emitter& emit_popad() {
    return emit(0x61);
  }

  /**
   * Emits a one-byte `POPF` instruction.
   *
   * @copydetails emit_general_purpose_instruction
   */
  x86_emitter& emit_popf() {
    return emit(0x9D);
  }

  /**
   * Emits a one-byte `POPFD` instruction.
   *
   * @copydetails emit_general_purpose_instruction
   */
  x86_emitter& emit_popfd() {
    return emit(0x9D);
  }

  /**
   * Emits a one-byte `POPFQ` instruction.
   *
   * @copydetails emit_general_purpose_instruction
   */
  x86_emitter& emit_popfq() {
    return emit(0x9D);
  }

  /**
   * Emits a one-byte `PUSHA` instruction.
   *
   * @copydetails emit_general_purpose_instruction
   */
  x86_emitter& emit_pusha() {
    return emit(0x60);
  }

  /**
   * Emits a one-byte `PUSHAD` instruction.
   *
   * @copydetails emit_general_purpose_instruction
   */
  x86_emitter& emit_pushad() {
    return emit(0x60);
  }

  /**
   * Emits a one-byte `PUSHF` instruction.
   *
   * @copydetails emit_general_purpose_instruction
   */
  x86_emitter& emit_pushf() {
    return emit(0x9C);
  }

  /**
   * Emits a one-byte `PUSHFD` instruction.
   *
   * @copydetails emit_general_purpose_instruction
   */
  x86_emitter& emit_pushfd() {
    return emit(0x9C);
  }

  /**
   * Emits a one-byte `PUSHFQ` instruction.
   *
   * @copydetails emit_general_purpose_instruction
   */
  x86_emitter& emit_pushfq() {
    return emit(0x9C);
  }

  /**
   * Emits a one-byte `RET` instruction.
   *
   * @copydetails emit_general_purpose_instruction
   */
  x86_emitter& emit_ret() {
    return emit(0xC3);
  }

  /**
   * Emits a one-byte `RETF` instruction.
   *
   * @copydetails emit_general_purpose_instruction
   */
  x86_emitter& emit_retf() {
    return emit(0xCB);
  }

  /**
   * Emits a one-byte `SAHF` instruction.
   *
   * @copydetails emit_general_purpose_instruction
   */
  x86_emitter& emit_sahf() {
    return emit(0x9E);
  }

  /**
   * Emits a one-byte `SCASB` instruction.
   *
   * @copydetails emit_general_purpose_instruction
   */
  x86_emitter& emit_scasb() {
    return emit(0xAE);
  }

  /**
   * Emits a one-byte `SCASW` instruction.
   *
   * @copydetails emit_general_purpose_instruction
   */
  x86_emitter& emit_scasw() {
    return emit(0xAF);
  }

  /**
   * Emits a one-byte `SCASD` instruction.
   *
   * @copydetails emit_general_purpose_instruction
   */
  x86_emitter& emit_scasd() {
    return emit(0xAF);
  }

  /**
   * Emits a one-byte `SCASQ` instruction.
   *
   * @copydetails emit_general_purpose_instruction
   */
  x86_emitter& emit_scasq() {
    return emit(0xAF);
  }

  /**
   * Emits a one-byte `STC` instruction.
   *
   * @copydetails emit_general_purpose_instruction
   */
  x86_emitter& emit_stc() {
    return emit(0xF9);
  }

  /**
   * Emits a one-byte `STD` instruction.
   *
   * @copydetails emit_general_purpose_instruction
   */
  x86_emitter& emit_std() {
    return emit(0xFD);
  }

  /**
   * Emits a one-byte `STOSB` instruction.
   *
   * @copydetails emit_general_purpose_instruction
   */
  x86_emitter& emit_stosb() {
    return emit(0xAA);
  }

  /**
   * Emits a one-byte `STOSW` instruction.
   *
   * @copydetails emit_general_purpose_instruction
   */
  x86_emitter& emit_stosw() {
    return emit(0xAB);
  }

  /**
   * Emits a one-byte `STOSD` instruction.
   *
   * @copydetails emit_general_purpose_instruction
   */
  x86_emitter& emit_stosd() {
    return emit(0xAB);
  }

  /**
   * Emits a one-byte `STOSQ` instruction.
   *
   * @copydetails emit_general_purpose_instruction
   */
  x86_emitter& emit_stosq() {
    return emit(0xAB);
  }

  /**
   * Emits a one-byte `XLATB` instruction.
   *
   * @copydetails emit_general_purpose_instruction
   */
  x86_emitter& emit_xlatb() {
    return emit(0xD7);
  }

  /**@}*/

  /**
   * @name System Instructions
   *
   * These instructions manipulate the processor operating mode, access
   * processor resources, handle program and system errors, and manage
   * system memory. Many of these instructions require privilege level 0 to
   * execute.
   */

  /**@{*/

  /**
   * @class emit_system_instruction
   *
   * @return `*this`
   * @throws std::bad_alloc if out of memory
   * @note This is a system instruction.
   */

  /**
   * Emits a three-byte `CLGI` instruction.
   *
   * @copydetails emit_system_instruction
   */
  x86_emitter& emit_clgi() {
    return emit(0x0F, 0x01, 0xDD);
  }

  /**
   * Emits a one-byte `CLI` instruction.
   *
   * @copydetails emit_system_instruction
   */
  x86_emitter& emit_cli() {
    return emit(0xFA);
  }

  /**
   * Emits a two-byte `CLTS` instruction.
   *
   * @copydetails emit_system_instruction
   */
  x86_emitter& emit_clts() {
    return emit(0x0F, 0x06);
  }

  /**
   * Emits a one-byte `HLT` instruction.
   *
   * @copydetails emit_system_instruction
   */
  x86_emitter& emit_hlt() {
    return emit(0xF4);
  }

  /**
   * Emits a one-byte `INT3` instruction.
   *
   * @copydetails emit_system_instruction
   */
  x86_emitter& emit_int3() {
    return emit(0xCC);
  }

  /**
   * Emits a two-byte `INVD` instruction.
   *
   * @copydetails emit_system_instruction
   */
  x86_emitter& emit_invd() {
    return emit(0x0F, 0x08);
  }

  /**
   * Emits a three-byte `INVLPGA` instruction.
   *
   * @copydetails emit_system_instruction
   */
  x86_emitter& emit_invlpga() {
    return emit(0x0F, 0x01, 0xDF);
  }

  /**
   * Emits a one-byte `IRET` instruction.
   *
   * @copydetails emit_system_instruction
   */
  x86_emitter& emit_iret() {
    return emit(0xCF);
  }

  /**
   * Emits a one-byte `IRETD` instruction.
   *
   * @copydetails emit_system_instruction
   */
  x86_emitter& emit_iretd() {
    return emit(0xCF);
  }

  /**
   * Emits a one-byte `IRETQ` instruction.
   *
   * @copydetails emit_system_instruction
   */
  x86_emitter& emit_iretq() {
    return emit(0xCF);
  }

  /**
   * Emits a three-byte `MONITOR` instruction.
   *
   * @copydetails emit_system_instruction
   */
  x86_emitter& emit_monitor() {
    return emit(0x0F, 0x01, 0xC8);
  }

  /**
   * Emits a three-byte `MWAIT` instruction.
   *
   * @copydetails emit_system_instruction
   */
  x86_emitter& emit_mwait() {
    return emit(0x0F, 0x01, 0xC9);
  }

  /**
   * Emits a two-byte `RDMSR` instruction.
   *
   * @copydetails emit_system_instruction
   */
  x86_emitter& emit_rdmsr() {
    return emit(0x0F, 0x32);
  }

  /**
   * Emits a two-byte `RDPMC` instruction.
   *
   * @copydetails emit_system_instruction
   */
  x86_emitter& emit_rdpmc() {
    return emit(0x0F, 0x33);
  }

  /**
   * Emits a two-byte `RDTSC` instruction.
   *
   * @copydetails emit_system_instruction
   */
  x86_emitter& emit_rdtsc() {
    return emit(0x0F, 0x31);
  }

  /**
   * Emits a three-byte `RDTSCP` instruction.
   *
   * @copydetails emit_system_instruction
   */
  x86_emitter& emit_rdtscp() {
    return emit(0x0F, 0x01, 0xF9);
  }

  /**
   * Emits a two-byte `RSM` instruction.
   *
   * @copydetails emit_system_instruction
   */
  x86_emitter& emit_rsm() {
    return emit(0x0F, 0xAA);
  }

  /**
   * Emits a three-byte `SKINIT` instruction.
   *
   * @copydetails emit_system_instruction
   */
  x86_emitter& emit_skinit() {
    return emit(0x0F, 0x01, 0xDE);
  }

  /**
   * Emits a one-byte `STI` instruction.
   *
   * @copydetails emit_system_instruction
   */
  x86_emitter& emit_sti() {
    return emit(0xFB);
  }

  /**
   * Emits a three-byte `STGI` instruction.
   *
   * @copydetails emit_system_instruction
   */
  x86_emitter& emit_stgi() {
    return emit(0x0F, 0x01, 0xDC);
  }

  /**
   * Emits a three-byte `SWAPGS` instruction.
   *
   * @copydetails emit_system_instruction
   */
  x86_emitter& emit_swapgs() {
    return emit(0x0F, 0x01, 0xF8);
  }

  /**
   * Emits a two-byte `SYSCALL` instruction.
   *
   * @copydetails emit_system_instruction
   */
  x86_emitter& emit_syscall() {
    return emit(0x0F, 0x05);
  }

  /**
   * Emits a two-byte `SYSENTER` instruction.
   *
   * @copydetails emit_system_instruction
   */
  x86_emitter& emit_sysenter() {
    return emit(0x0F, 0x34);
  }

  /**
   * Emits a two-byte `SYSEXIT` instruction.
   *
   * @copydetails emit_system_instruction
   */
  x86_emitter& emit_sysexit() {
    return emit(0x0F, 0x35);
  }

  /**
   * Emits a two-byte `SYSRET` instruction.
   *
   * @copydetails emit_system_instruction
   */
  x86_emitter& emit_sysret() {
    return emit(0x0F, 0x07);
  }

  /**
   * Emits a two-byte `UD2` instruction.
   *
   * @copydetails emit_system_instruction
   */
  x86_emitter& emit_ud2() {
    return emit(0x0F, 0x0B);
  }

  /**
   * Emits a three-byte `VMLOAD` instruction.
   *
   * @copydetails emit_system_instruction
   */
  x86_emitter& emit_vmload() {
    return emit(0x0F, 0x01, 0xDA);
  }

  /**
   * Emits a three-byte `VMMCALL` instruction.
   *
   * @copydetails emit_system_instruction
   */
  x86_emitter& emit_vmmcall() {
    return emit(0x0F, 0x01, 0xD9);
  }

  /**
   * Emits a three-byte `VMRUN` instruction.
   *
   * @copydetails emit_system_instruction
   */
  x86_emitter& emit_vmrun() {
    return emit(0x0F, 0x01, 0xD8);
  }

  /**
   * Emits a three-byte `VMSAVE` instruction.
   *
   * @copydetails emit_system_instruction
   */
  x86_emitter& emit_vmsave() {
    return emit(0x0F, 0x01, 0xDB);
  }

  /**
   * Emits a two-byte `WBINVD` instruction.
   *
   * @copydetails emit_system_instruction
   */
  x86_emitter& emit_wbinvd() {
    return emit(0x0F, 0x09);
  }

  /**
   * Emits a two-byte `WRMSR` instruction.
   *
   * @copydetails emit_system_instruction
   */
  x86_emitter& emit_wrmsr() {
    return emit(0x0F, 0x30);
  }

  /**@}*/

  /**
   * @name x87 Instructions
   */

  /**@{*/

  /**@}*/

  /**
   * @name MMX Instructions
   */

  /**@{*/

  /**@}*/

  /**
   * @name SSE Instructions
   */

  /**@{*/

  /**@}*/
};

#endif /* MACHINERY_ARCH_X86_EMITTER_H */
