/* This is free and unencumbered software released into the public domain. */

#ifndef MACHINERY_ARCH_X86_EMITTER_H
#define MACHINERY_ARCH_X86_EMITTER_H

/**
 * @file
 *
 * x86 machine code emission.
 */

#include "encoding.h"

#include <cstddef>   /* for std::size_t */
#include <cstdint>   /* for std::uint8_t */
#include <stdexcept> /* for std::runtime_error */

namespace machinery {
  namespace arch {
    template<class Buffer> class x86_emitter;
  }
}

/**
 * x86 machine code emitter.
 *
 * @note Instances of this class are movable, but not copyable.
 */
template <class Buffer>
class machinery::arch::x86_emitter {
  Buffer& _buffer;
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
  x86_emitter(Buffer& buffer) noexcept
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
    _buffer.append(opcode);
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
    _buffer.append({opcode, opcode2});
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
    _buffer.append({opcode, opcode2, opcode3});
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
    _buffer.append(imm.u8);
    return *this;
  }

  /**
   * Emits a 16-bit immediate value.
   *
   * @copydetails emit_immediate_value
   */
  inline x86_emitter& emit(x86_imm16 imm) {
    for (auto i = 0; i < 2; i++) {
      _buffer.append(imm.u16 & 0xFF);
      imm.u16 >>= 8;
    }
    return *this;
  }

  /**
   * Emits a 32-bit immediate value.
   *
   * @copydetails emit_immediate_value
   */
  inline x86_emitter& emit(x86_imm32 imm) {
    for (auto i = 0; i < 4; i++) {
      _buffer.append(imm.u32 & 0xFF);
      imm.u32 >>= 8;
    }
    return *this;
  }

  /**
   * Emits a 64-bit immediate value.
   *
   * @copydetails emit_immediate_value
   */
  inline x86_emitter& emit(x86_imm64 imm) {
    for (auto i = 0; i < 8; i++) {
      _buffer.append(imm.u64 & 0xFF);
      imm.u64 >>= 8;
    }
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
  x86_emitter& aaa() {
    return emit(0x37);
  }

  /**
   * Emits a one-byte `AAS` instruction.
   *
   * @copydetails emit_general_purpose_instruction
   */
  x86_emitter& aas() {
    return emit(0x3F);
  }

  /**
   * Emits a two-byte `ADD AL, imm8` instruction.
   *
   * @param imm the 8-bit immediate value operand
   * @copydetails emit_general_purpose_instruction
   */
  x86_emitter& add(const x86_imm8 imm) {
    return emit(0x04).emit(imm);
  }

  /**
   * Emits a four-byte `ADD AX, imm16` instruction.
   *
   * @param imm the 16-bit immediate value operand
   * @copydetails emit_general_purpose_instruction
   */
  x86_emitter& add(const x86_imm16 imm) {
    return emit(0x66, 0x05).emit(imm);
  }

  /**
   * Emits a five-byte `ADD EAX, imm32` instruction.
   *
   * @param imm the 32-bit immediate value operand
   * @copydetails emit_general_purpose_instruction
   */
  x86_emitter& add(const x86_imm32 imm) {
    return emit(0x05).emit(imm);
  }

  /**
   * Emits a six-byte `ADD RAX, imm64` instruction.
   *
   * @param imm the 64-bit immediate value operand
   * @copydetails emit_general_purpose_instruction
   */
  x86_emitter& add(const x86_imm64 imm) {
    // TODO: synthesize ops if imm > INT32_MAX?
    return emit(0x48, 0x05).emit(static_cast<x86_imm32>(imm.s64));
  }

  /**
   * Emits a one-byte `CBW` instruction.
   *
   * @copydetails emit_general_purpose_instruction
   */
  x86_emitter& cbw() {
    return emit(0x98);
  }

  /**
   * Emits a one-byte `CWDE` instruction.
   *
   * @copydetails emit_general_purpose_instruction
   */
  x86_emitter& cwde() {
    return emit(0x98);
  }

  /**
   * Emits a one-byte `CDQE` instruction.
   *
   * @copydetails emit_general_purpose_instruction
   */
  x86_emitter& cdqe() {
    return emit(0x98);
  }

  /**
   * Emits a one-byte `CWD` instruction.
   *
   * @copydetails emit_general_purpose_instruction
   */
  x86_emitter& cwd() {
    return emit(0x99);
  }

  /**
   * Emits a one-byte `CDQ` instruction.
   *
   * @copydetails emit_general_purpose_instruction
   */
  x86_emitter& cdq() {
    return emit(0x99);
  }

  /**
   * Emits a one-byte `CQO` instruction.
   *
   * @copydetails emit_general_purpose_instruction
   */
  x86_emitter& cqo() {
    return emit(0x99);
  }

  /**
   * Emits a one-byte `CLC` instruction.
   *
   * @copydetails emit_general_purpose_instruction
   */
  x86_emitter& clc() {
    return emit(0xF8);
  }

  /**
   * Emits a one-byte `CLD` instruction.
   *
   * @copydetails emit_general_purpose_instruction
   */
  x86_emitter& cld() {
    return emit(0xFC);
  }

  /**
   * Emits a one-byte `CMC` instruction.
   *
   * @copydetails emit_general_purpose_instruction
   */
  x86_emitter& cmc() {
    return emit(0xF5);
  }

  /**
   * Emits a one-byte `CMPSB` instruction.
   *
   * @copydetails emit_general_purpose_instruction
   */
  x86_emitter& cmpsb() {
    return emit(0xA6);
  }

  /**
   * Emits a one-byte `CMPSW` instruction.
   *
   * @copydetails emit_general_purpose_instruction
   */
  x86_emitter& cmpsw() {
    return emit(0xA7);
  }

  /**
   * Emits a one-byte `CMPSD` instruction.
   *
   * @copydetails emit_general_purpose_instruction
   */
  x86_emitter& cmpsd() {
    return emit(0xA7);
  }

  /**
   * Emits a one-byte `CMPSQ` instruction.
   *
   * @copydetails emit_general_purpose_instruction
   */
  x86_emitter& cmpsq() {
    return emit(0xA7);
  }

  /**
   * Emits a one-byte `DAA` instruction.
   *
   * @copydetails emit_general_purpose_instruction
   */
  x86_emitter& daa() {
    return emit(0x27);
  }

  /**
   * Emits a one-byte `DAS` instruction.
   *
   * @copydetails emit_general_purpose_instruction
   */
  x86_emitter& das() {
    return emit(0x2F);
  }

  /**
   * Emits a one-byte `INSB` instruction.
   *
   * @copydetails emit_general_purpose_instruction
   */
  x86_emitter& insb() {
    return emit(0x6C);
  }

  /**
   * Emits a one-byte `INSW` instruction.
   *
   * @copydetails emit_general_purpose_instruction
   */
  x86_emitter& insw() {
    return emit(0x6D);
  }

  /**
   * Emits a one-byte `INSD` instruction.
   *
   * @copydetails emit_general_purpose_instruction
   */
  x86_emitter& insd() {
    return emit(0x6D);
  }

  /**
   * Emits a one-byte `INTO` instruction.
   *
   * @copydetails emit_general_purpose_instruction
   */
  x86_emitter& into() {
    return emit(0xCE);
  }

  /**
   * Emits a one-byte `LAHF` instruction.
   *
   * @copydetails emit_general_purpose_instruction
   */
  x86_emitter& lahf() {
    return emit(0x9F);
  }

  /**
   * Emits a one-byte `LEAVE` instruction.
   *
   * @copydetails emit_general_purpose_instruction
   */
  x86_emitter& leave() {
    return emit(0xC9);
  }

  /**
   * Emits a one-byte `LODSB` instruction.
   *
   * @copydetails emit_general_purpose_instruction
   */
  x86_emitter& lodsb() {
    return emit(0xAC);
  }

  /**
   * Emits a one-byte `LODSW` instruction.
   *
   * @copydetails emit_general_purpose_instruction
   */
  x86_emitter& lodsw() {
    return emit(0xAD);
  }

  /**
   * Emits a one-byte `LODSD` instruction.
   *
   * @copydetails emit_general_purpose_instruction
   */
  x86_emitter& lodsd() {
    return emit(0xAD);
  }

  /**
   * Emits a one-byte `LODSQ` instruction.
   *
   * @copydetails emit_general_purpose_instruction
   */
  x86_emitter& lodsq() {
    return emit(0xAD);
  }

  /**
   * Emits a two-byte `MOV reg8, imm8` instruction.
   *
   * @param reg the 8-bit target register operand
   * @param imm the 8-bit immediate value operand
   * @copydetails emit_general_purpose_instruction
   */
  x86_emitter& mov(const x86_reg8 reg,
                   const x86_imm8 imm) {
    return emit(0xB0 + static_cast<std::uint8_t>(reg)).emit(imm);
  }

  /**
   * Emits a four-byte `MOV reg16, imm16` instruction.
   *
   * @param reg the 16-bit target register operand
   * @param imm the 16-bit immediate value operand
   * @copydetails emit_general_purpose_instruction
   */
  x86_emitter& mov(const x86_reg16 reg,
                   const x86_imm16 imm) {
    return emit(0x66, 0xB8 + static_cast<std::uint8_t>(reg)).emit(imm);
  }

  /**
   * Emits a five-byte `MOV reg32, imm32` instruction.
   *
   * @param reg the 32-bit target register operand
   * @param imm the 32-bit immediate value operand
   * @copydetails emit_general_purpose_instruction
   */
  x86_emitter& mov(const x86_reg32 reg,
                   const x86_imm32 imm) {
    return emit(0xB8 + static_cast<std::uint8_t>(reg)).emit(imm);
  }

  /**
   * Emits a ten-byte `MOV reg64, imm64` instruction.
   *
   * @param reg the 64-bit target register operand
   * @param imm the 64-bit immediate value operand
   * @copydetails emit_general_purpose_instruction
   */
  x86_emitter& mov(const x86_reg64 reg,
                   const x86_imm64 imm) {
    //assert(reg < x86_reg64::r8); // FIXME
    return emit(0x48, 0xB8 + static_cast<std::uint8_t>(reg)).emit(imm); // FIXME
  }

  /**
   * Emits a `MOV reg64, reg64` instruction.
   *
   * @param reg1 the 64-bit target register operand
   * @param reg2 the 64-bit source register operand
   * @copydetails emit_general_purpose_instruction
   */
  x86_emitter& mov(const x86_reg64 reg1,
                   const x86_reg64 reg2) {
    if (reg1 == x86_reg64::rbp && reg2 == x86_reg64::rsp)
      return emit(0x48, 0x89, 0xE5);
    throw std::runtime_error("not implemented yet"); // TODO
  }

  /**
   * Emits a one-byte `MOVSB` instruction.
   *
   * @copydetails emit_general_purpose_instruction
   */
  x86_emitter& movsb() {
    return emit(0xA4);
  }

  /**
   * Emits a one-byte `MOVSW` instruction.
   *
   * @copydetails emit_general_purpose_instruction
   */
  x86_emitter& movsw() {
    return emit(0xA5);
  }

  /**
   * Emits a one-byte `MOVSD` instruction.
   *
   * @copydetails emit_general_purpose_instruction
   */
  x86_emitter& movsd() {
    return emit(0xA5);
  }

  /**
   * Emits a one-byte `MOVSQ` instruction.
   *
   * @copydetails emit_general_purpose_instruction
   */
  x86_emitter& movsq() {
    return emit(0xA5);
  }

  /**
   * Emits a ?-byte `MUL reg8` instruction.
   *
   * @param reg8 an 8-bit register operand
   * @todo Implement this method.
   * @copydetails emit_general_purpose_instruction
   */
  x86_emitter& mul(const x86_reg8 reg) {
    throw std::runtime_error("not implemented yet"); // TODO
    return (void)reg, *this; // TODO
  }

  /**
   * Emits a ?-byte `MUL reg16` instruction.
   *
   * @param reg a 16-bit register operand
   * @todo Implement this method.
   * @copydetails emit_general_purpose_instruction
   */
  x86_emitter& mul(const x86_reg16 reg) {
    throw std::runtime_error("not implemented yet"); // TODO
    return (void)reg, *this; // TODO
  }

  /**
   * Emits a ?-byte `MUL reg32` instruction.
   *
   * @param reg a 32-bit register operand
   * @todo Implement this method.
   * @copydetails emit_general_purpose_instruction
   */
  x86_emitter& mul(const x86_reg32 reg) {
    throw std::runtime_error("not implemented yet"); // TODO
    return (void)reg, *this; // TODO
  }

  /**
   * Emits a ?-byte `MUL reg32` instruction.
   *
   * @param reg a 64-bit register operand
   * @todo Implement this method.
   * @copydetails emit_general_purpose_instruction
   */
  x86_emitter& mul(const x86_reg64 reg) {
    throw std::runtime_error("not implemented yet"); // TODO
    return (void)reg, *this; // TODO
  }

  /**
   * Emits a one-byte `NOP` instruction.
   *
   * @copydetails emit_general_purpose_instruction
   */
  x86_emitter& nop() {
    return emit(0x90);
  }

  /**
   * Emits a one-byte `OUTSB` instruction.
   *
   * @copydetails emit_general_purpose_instruction
   */
  x86_emitter& outsb() {
    return emit(0x6E);
  }

  /**
   * Emits a one-byte `OUTSW` instruction.
   *
   * @copydetails emit_general_purpose_instruction
   */
  x86_emitter& outsw() {
    return emit(0x6F);
  }

  /**
   * Emits a one-byte `OUTSD` instruction.
   *
   * @copydetails emit_general_purpose_instruction
   */
  x86_emitter& outsd() {
    return emit(0x6F);
  }

  /**
   * Emits a one-byte `POP reg16` instruction.
   *
   * @param reg a 16-bit register operand
   * @copydetails emit_general_purpose_instruction
   */
  x86_emitter& pop(const x86_reg16 reg) {
    return emit(0x58 + static_cast<std::uint8_t>(reg));
  }

  /**
   * Emits a one-byte `POP reg32` instruction.
   *
   * @param reg a 32-bit register operand
   * @copydetails emit_general_purpose_instruction
   */
  x86_emitter& pop(const x86_reg32 reg) {
    return emit(0x58 + static_cast<std::uint8_t>(reg));
  }

  /**
   * Emits a one-byte `POP reg64` instruction.
   *
   * @param reg a 64-bit register operand
   * @copydetails emit_general_purpose_instruction
   */
  x86_emitter& pop(const x86_reg64 reg) {
    return emit(0x58 + static_cast<std::uint8_t>(reg));
  }

  /**
   * Emits a one-byte `POPA` instruction.
   *
   * @copydetails emit_general_purpose_instruction
   */
  x86_emitter& popa() {
    return emit(0x61);
  }

  /**
   * Emits a one-byte `POPAD` instruction.
   *
   * @copydetails emit_general_purpose_instruction
   */
  x86_emitter& popad() {
    return emit(0x61);
  }

  /**
   * Emits a one-byte `POPF` instruction.
   *
   * @copydetails emit_general_purpose_instruction
   */
  x86_emitter& popf() {
    return emit(0x9D);
  }

  /**
   * Emits a one-byte `POPFD` instruction.
   *
   * @copydetails emit_general_purpose_instruction
   */
  x86_emitter& popfd() {
    return emit(0x9D);
  }

  /**
   * Emits a one-byte `POPFQ` instruction.
   *
   * @copydetails emit_general_purpose_instruction
   */
  x86_emitter& popfq() {
    return emit(0x9D);
  }

  /**
   * Emits a one-byte `PUSH reg16` instruction.
   *
   * @param reg a 16-bit register operand
   * @copydetails emit_general_purpose_instruction
   */
  x86_emitter& push(const x86_reg16 reg) {
    return emit(0x50 + static_cast<std::uint8_t>(reg));
  }

  /**
   * Emits a one-byte `PUSH reg32` instruction.
   *
   * @param reg a 32-bit register operand
   * @copydetails emit_general_purpose_instruction
   */
  x86_emitter& push(const x86_reg32 reg) {
    return emit(0x50 + static_cast<std::uint8_t>(reg));
  }

  /**
   * Emits a one-byte `PUSH reg64` instruction.
   *
   * @param reg a 64-bit register operand
   * @copydetails emit_general_purpose_instruction
   */
  x86_emitter& push(const x86_reg64 reg) {
    return emit(0x50 + static_cast<std::uint8_t>(reg));
  }

  /**
   * Emits a one-byte `PUSHA` instruction.
   *
   * @copydetails emit_general_purpose_instruction
   */
  x86_emitter& pusha() {
    return emit(0x60);
  }

  /**
   * Emits a one-byte `PUSHAD` instruction.
   *
   * @copydetails emit_general_purpose_instruction
   */
  x86_emitter& pushad() {
    return emit(0x60);
  }

  /**
   * Emits a one-byte `PUSHF` instruction.
   *
   * @copydetails emit_general_purpose_instruction
   */
  x86_emitter& pushf() {
    return emit(0x9C);
  }

  /**
   * Emits a one-byte `PUSHFD` instruction.
   *
   * @copydetails emit_general_purpose_instruction
   */
  x86_emitter& pushfd() {
    return emit(0x9C);
  }

  /**
   * Emits a one-byte `PUSHFQ` instruction.
   *
   * @copydetails emit_general_purpose_instruction
   */
  x86_emitter& pushfq() {
    return emit(0x9C);
  }

  /**
   * Emits a one-byte `RET` instruction.
   *
   * @copydetails emit_general_purpose_instruction
   */
  x86_emitter& ret() {
    return emit(0xC3);
  }

  /**
   * Emits a one-byte `RETF` instruction.
   *
   * @copydetails emit_general_purpose_instruction
   */
  x86_emitter& retf() {
    return emit(0xCB);
  }

  /**
   * Emits a one-byte `SAHF` instruction.
   *
   * @copydetails emit_general_purpose_instruction
   */
  x86_emitter& sahf() {
    return emit(0x9E);
  }

  /**
   * Emits a one-byte `SCASB` instruction.
   *
   * @copydetails emit_general_purpose_instruction
   */
  x86_emitter& scasb() {
    return emit(0xAE);
  }

  /**
   * Emits a one-byte `SCASW` instruction.
   *
   * @copydetails emit_general_purpose_instruction
   */
  x86_emitter& scasw() {
    return emit(0xAF);
  }

  /**
   * Emits a one-byte `SCASD` instruction.
   *
   * @copydetails emit_general_purpose_instruction
   */
  x86_emitter& scasd() {
    return emit(0xAF);
  }

  /**
   * Emits a one-byte `SCASQ` instruction.
   *
   * @copydetails emit_general_purpose_instruction
   */
  x86_emitter& scasq() {
    return emit(0xAF);
  }

  /**
   * Emits a one-byte `STC` instruction.
   *
   * @copydetails emit_general_purpose_instruction
   */
  x86_emitter& stc() {
    return emit(0xF9);
  }

  /**
   * Emits a one-byte `STD` instruction.
   *
   * @copydetails emit_general_purpose_instruction
   */
  x86_emitter& std() {
    return emit(0xFD);
  }

  /**
   * Emits a one-byte `STOSB` instruction.
   *
   * @copydetails emit_general_purpose_instruction
   */
  x86_emitter& stosb() {
    return emit(0xAA);
  }

  /**
   * Emits a one-byte `STOSW` instruction.
   *
   * @copydetails emit_general_purpose_instruction
   */
  x86_emitter& stosw() {
    return emit(0xAB);
  }

  /**
   * Emits a one-byte `STOSD` instruction.
   *
   * @copydetails emit_general_purpose_instruction
   */
  x86_emitter& stosd() {
    return emit(0xAB);
  }

  /**
   * Emits a one-byte `STOSQ` instruction.
   *
   * @copydetails emit_general_purpose_instruction
   */
  x86_emitter& stosq() {
    return emit(0xAB);
  }

  /**
   * Emits a one-byte `XLATB` instruction.
   *
   * @copydetails emit_general_purpose_instruction
   */
  x86_emitter& xlatb() {
    return emit(0xD7);
  }

  /**
   * Emits a ?-byte `XOR reg8, reg8` instruction.
   *
   * @param reg1 an 8-bit register operand
   * @param reg2 an 8-bit register operand
   * @copydetails emit_general_purpose_instruction
   */
  x86_emitter& xor_(const x86_reg8 reg1,
                    const x86_reg8 reg2) {
    throw std::runtime_error("not implemented yet"); // TODO
    return (void)reg1, (void)reg2, *this;
  }

  /**
   * Emits a ?-byte `XOR reg16, reg16` instruction.
   *
   * @param reg1 a 16-bit register operand
   * @param reg2 a 16-bit register operand
   * @copydetails emit_general_purpose_instruction
   */
  x86_emitter& xor_(const x86_reg16 reg1,
                    const x86_reg16 reg2) {
    throw std::runtime_error("not implemented yet"); // TODO
    return (void)reg1, (void)reg2, *this;
  }

  /**
   * Emits a ?-byte `XOR reg32, reg32` instruction.
   *
   * @param reg1 a 32-bit register operand
   * @param reg2 a 32-bit register operand
   * @copydetails emit_general_purpose_instruction
   */
  x86_emitter& xor_(const x86_reg32 reg1,
                    const x86_reg32 reg2) {
    throw std::runtime_error("not implemented yet"); // TODO
    return (void)reg1, (void)reg2, *this;
  }

  /**
   * Emits a ?-byte `XOR reg64, reg64` instruction.
   *
   * @param reg1 a 64-bit register operand
   * @param reg2 a 64-bit register operand
   * @copydetails emit_general_purpose_instruction
   */
  x86_emitter& xor_(const x86_reg64 reg1,
                    const x86_reg64 reg2) {
    throw std::runtime_error("not implemented yet"); // TODO
    return (void)reg1, (void)reg2, *this;
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
  x86_emitter& clgi() {
    return emit(0x0F, 0x01, 0xDD);
  }

  /**
   * Emits a one-byte `CLI` instruction.
   *
   * @copydetails emit_system_instruction
   */
  x86_emitter& cli() {
    return emit(0xFA);
  }

  /**
   * Emits a two-byte `CLTS` instruction.
   *
   * @copydetails emit_system_instruction
   */
  x86_emitter& clts() {
    return emit(0x0F, 0x06);
  }

  /**
   * Emits a one-byte `HLT` instruction.
   *
   * @copydetails emit_system_instruction
   */
  x86_emitter& hlt() {
    return emit(0xF4);
  }

  /**
   * Emits a one-byte `INT3` instruction.
   *
   * @copydetails emit_system_instruction
   */
  x86_emitter& int3() {
    return emit(0xCC);
  }

  /**
   * Emits a two-byte `INVD` instruction.
   *
   * @copydetails emit_system_instruction
   */
  x86_emitter& invd() {
    return emit(0x0F, 0x08);
  }

  /**
   * Emits a three-byte `INVLPGA` instruction.
   *
   * @copydetails emit_system_instruction
   */
  x86_emitter& invlpga() {
    return emit(0x0F, 0x01, 0xDF);
  }

  /**
   * Emits a one-byte `IRET` instruction.
   *
   * @copydetails emit_system_instruction
   */
  x86_emitter& iret() {
    return emit(0xCF);
  }

  /**
   * Emits a one-byte `IRETD` instruction.
   *
   * @copydetails emit_system_instruction
   */
  x86_emitter& iretd() {
    return emit(0xCF);
  }

  /**
   * Emits a one-byte `IRETQ` instruction.
   *
   * @copydetails emit_system_instruction
   */
  x86_emitter& iretq() {
    return emit(0xCF);
  }

  /**
   * Emits a three-byte `MONITOR` instruction.
   *
   * @copydetails emit_system_instruction
   */
  x86_emitter& monitor() {
    return emit(0x0F, 0x01, 0xC8);
  }

  /**
   * Emits a three-byte `MWAIT` instruction.
   *
   * @copydetails emit_system_instruction
   */
  x86_emitter& mwait() {
    return emit(0x0F, 0x01, 0xC9);
  }

  /**
   * Emits a two-byte `RDMSR` instruction.
   *
   * @copydetails emit_system_instruction
   */
  x86_emitter& rdmsr() {
    return emit(0x0F, 0x32);
  }

  /**
   * Emits a two-byte `RDPMC` instruction.
   *
   * @copydetails emit_system_instruction
   */
  x86_emitter& rdpmc() {
    return emit(0x0F, 0x33);
  }

  /**
   * Emits a two-byte `RDTSC` instruction.
   *
   * @copydetails emit_system_instruction
   */
  x86_emitter& rdtsc() {
    return emit(0x0F, 0x31);
  }

  /**
   * Emits a three-byte `RDTSCP` instruction.
   *
   * @copydetails emit_system_instruction
   */
  x86_emitter& rdtscp() {
    return emit(0x0F, 0x01, 0xF9);
  }

  /**
   * Emits a two-byte `RSM` instruction.
   *
   * @copydetails emit_system_instruction
   */
  x86_emitter& rsm() {
    return emit(0x0F, 0xAA);
  }

  /**
   * Emits a three-byte `SKINIT` instruction.
   *
   * @copydetails emit_system_instruction
   */
  x86_emitter& skinit() {
    return emit(0x0F, 0x01, 0xDE);
  }

  /**
   * Emits a one-byte `STI` instruction.
   *
   * @copydetails emit_system_instruction
   */
  x86_emitter& sti() {
    return emit(0xFB);
  }

  /**
   * Emits a three-byte `STGI` instruction.
   *
   * @copydetails emit_system_instruction
   */
  x86_emitter& stgi() {
    return emit(0x0F, 0x01, 0xDC);
  }

  /**
   * Emits a three-byte `SWAPGS` instruction.
   *
   * @copydetails emit_system_instruction
   */
  x86_emitter& swapgs() {
    return emit(0x0F, 0x01, 0xF8);
  }

  /**
   * Emits a two-byte `SYSCALL` instruction.
   *
   * @copydetails emit_system_instruction
   */
  x86_emitter& syscall() {
    return emit(0x0F, 0x05);
  }

  /**
   * Emits a two-byte `SYSENTER` instruction.
   *
   * @copydetails emit_system_instruction
   */
  x86_emitter& sysenter() {
    return emit(0x0F, 0x34);
  }

  /**
   * Emits a two-byte `SYSEXIT` instruction.
   *
   * @copydetails emit_system_instruction
   */
  x86_emitter& sysexit() {
    return emit(0x0F, 0x35);
  }

  /**
   * Emits a two-byte `SYSRET` instruction.
   *
   * @copydetails emit_system_instruction
   */
  x86_emitter& sysret() {
    return emit(0x0F, 0x07);
  }

  /**
   * Emits a two-byte `UD2` instruction.
   *
   * @copydetails emit_system_instruction
   */
  x86_emitter& ud2() {
    return emit(0x0F, 0x0B);
  }

  /**
   * Emits a three-byte `VMLOAD` instruction.
   *
   * @copydetails emit_system_instruction
   */
  x86_emitter& vmload() {
    return emit(0x0F, 0x01, 0xDA);
  }

  /**
   * Emits a three-byte `VMMCALL` instruction.
   *
   * @copydetails emit_system_instruction
   */
  x86_emitter& vmmcall() {
    return emit(0x0F, 0x01, 0xD9);
  }

  /**
   * Emits a three-byte `VMRUN` instruction.
   *
   * @copydetails emit_system_instruction
   */
  x86_emitter& vmrun() {
    return emit(0x0F, 0x01, 0xD8);
  }

  /**
   * Emits a three-byte `VMSAVE` instruction.
   *
   * @copydetails emit_system_instruction
   */
  x86_emitter& vmsave() {
    return emit(0x0F, 0x01, 0xDB);
  }

  /**
   * Emits a two-byte `WBINVD` instruction.
   *
   * @copydetails emit_system_instruction
   */
  x86_emitter& wbinvd() {
    return emit(0x0F, 0x09);
  }

  /**
   * Emits a two-byte `WRMSR` instruction.
   *
   * @copydetails emit_system_instruction
   */
  x86_emitter& wrmsr() {
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
