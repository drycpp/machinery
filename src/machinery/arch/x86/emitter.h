/* This is free and unencumbered software released into the public domain. */

#ifndef MACHINERY_ARCH_X86_EMITTER_H
#define MACHINERY_ARCH_X86_EMITTER_H

/**
 * @file
 */

#include <cstdint> /* for std::uint8_t */
#include <vector>  /* for std::vector */

namespace machinery {
  namespace arch {
    class x86_emitter;
    using x86_opcode = std::uint8_t; /**< x86 opcode byte */
  }
}

/**
 * x86 machine code emitter.
 *
 * @note Instances of this class are movable, but not copyable.
 */
class machinery::arch::x86_emitter {
  std::vector<std::uint8_t>& _buffer;

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
    : _buffer(buffer) {}

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
   * Emits a one-byte instruction.
   *
   * @param opcode the opcode byte
   * @return `*this`
   * @throws std::bad_alloc if out of memory
   */
  inline x86_emitter& emit(const x86_opcode opcode) {
    _buffer.push_back(opcode);
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
    _buffer.push_back(opcode);
    _buffer.push_back(opcode2);
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
    _buffer.push_back(opcode);
    _buffer.push_back(opcode2);
    _buffer.push_back(opcode3);
    return *this;
  }

  /**
   * Emits a one-byte `AAA` instruction.
   *
   * @return `*this`
   * @throws std::bad_alloc if out of memory
   */
  x86_emitter& emit_aaa() {
    return emit(0x37);
  }

  /**
   * Emits a one-byte `AAS` instruction.
   *
   * @return `*this`
   * @throws std::bad_alloc if out of memory
   */
  x86_emitter& emit_aas() {
    return emit(0x3F);
  }

  /**
   * Emits a one-byte `CBW` instruction.
   *
   * @return `*this`
   * @throws std::bad_alloc if out of memory
   */
  x86_emitter& emit_cbw() {
    return emit(0x98);
  }

  /**
   * Emits a one-byte `CWDE` instruction.
   *
   * @return `*this`
   * @throws std::bad_alloc if out of memory
   */
  x86_emitter& emit_cwde() {
    return emit(0x98);
  }

  /**
   * Emits a one-byte `CDQE` instruction.
   *
   * @return `*this`
   * @throws std::bad_alloc if out of memory
   */
  x86_emitter& emit_cdqe() {
    return emit(0x98);
  }

  /**
   * Emits a one-byte `CWD` instruction.
   *
   * @return `*this`
   * @throws std::bad_alloc if out of memory
   */
  x86_emitter& emit_cwd() {
    return emit(0x99);
  }

  /**
   * Emits a one-byte `CDQ` instruction.
   *
   * @return `*this`
   * @throws std::bad_alloc if out of memory
   */
  x86_emitter& emit_cdq() {
    return emit(0x99);
  }

  /**
   * Emits a one-byte `CQO` instruction.
   *
   * @return `*this`
   * @throws std::bad_alloc if out of memory
   */
  x86_emitter& emit_cqo() {
    return emit(0x99);
  }

  /**
   * Emits a one-byte `CLC` instruction.
   *
   * @return `*this`
   * @throws std::bad_alloc if out of memory
   */
  x86_emitter& emit_clc() {
    return emit(0xF8);
  }

  /**
   * Emits a one-byte `CLD` instruction.
   *
   * @return `*this`
   * @throws std::bad_alloc if out of memory
   */
  x86_emitter& emit_cld() {
    return emit(0xFC);
  }

  /**
   * Emits a one-byte `CMC` instruction.
   *
   * @return `*this`
   * @throws std::bad_alloc if out of memory
   */
  x86_emitter& emit_cmc() {
    return emit(0xF5);
  }

  /**
   * Emits a one-byte `CMPSB` instruction.
   *
   * @return `*this`
   * @throws std::bad_alloc if out of memory
   */
  x86_emitter& emit_cmpsb() {
    return emit(0xA6);
  }

  /**
   * Emits a one-byte `CMPSW` instruction.
   *
   * @return `*this`
   * @throws std::bad_alloc if out of memory
   */
  x86_emitter& emit_cmpsw() {
    return emit(0xA7);
  }

  /**
   * Emits a one-byte `CMPSD` instruction.
   *
   * @return `*this`
   * @throws std::bad_alloc if out of memory
   */
  x86_emitter& emit_cmpsd() {
    return emit(0xA7);
  }

  /**
   * Emits a one-byte `CMPSQ` instruction.
   *
   * @return `*this`
   * @throws std::bad_alloc if out of memory
   */
  x86_emitter& emit_cmpsq() {
    return emit(0xA7);
  }

  /**
   * Emits a one-byte `DAA` instruction.
   *
   * @return `*this`
   * @throws std::bad_alloc if out of memory
   */
  x86_emitter& emit_daa() {
    return emit(0x27);
  }

  /**
   * Emits a one-byte `DAS` instruction.
   *
   * @return `*this`
   * @throws std::bad_alloc if out of memory
   */
  x86_emitter& emit_das() {
    return emit(0x2F);
  }

  /**
   * Emits a one-byte `INSB` instruction.
   *
   * @return `*this`
   * @throws std::bad_alloc if out of memory
   */
  x86_emitter& emit_insb() {
    return emit(0x6C);
  }

  /**
   * Emits a one-byte `INSW` instruction.
   *
   * @return `*this`
   * @throws std::bad_alloc if out of memory
   */
  x86_emitter& emit_insw() {
    return emit(0x6D);
  }

  /**
   * Emits a one-byte `INSD` instruction.
   *
   * @return `*this`
   * @throws std::bad_alloc if out of memory
   */
  x86_emitter& emit_insd() {
    return emit(0x6D);
  }

  /**
   * Emits a one-byte `INTO` instruction.
   *
   * @return `*this`
   * @throws std::bad_alloc if out of memory
   */
  x86_emitter& emit_into() {
    return emit(0xCE);
  }

  /**
   * Emits a one-byte `LAHF` instruction.
   *
   * @return `*this`
   * @throws std::bad_alloc if out of memory
   */
  x86_emitter& emit_lahf() {
    return emit(0x9F);
  }

  /**
   * Emits a one-byte `LEAVE` instruction.
   *
   * @return `*this`
   * @throws std::bad_alloc if out of memory
   */
  x86_emitter& emit_leave() {
    return emit(0xC9);
  }

  /**
   * Emits a one-byte `LODSB` instruction.
   *
   * @return `*this`
   * @throws std::bad_alloc if out of memory
   */
  x86_emitter& emit_lodsb() {
    return emit(0xAC);
  }

  /**
   * Emits a one-byte `LODSW` instruction.
   *
   * @return `*this`
   * @throws std::bad_alloc if out of memory
   */
  x86_emitter& emit_lodsw() {
    return emit(0xAD);
  }

  /**
   * Emits a one-byte `LODSD` instruction.
   *
   * @return `*this`
   * @throws std::bad_alloc if out of memory
   */
  x86_emitter& emit_lodsd() {
    return emit(0xAD);
  }

  /**
   * Emits a one-byte `LODSQ` instruction.
   *
   * @return `*this`
   * @throws std::bad_alloc if out of memory
   */
  x86_emitter& emit_lodsq() {
    return emit(0xAD);
  }

  /**
   * Emits a one-byte `MOVSB` instruction.
   *
   * @return `*this`
   * @throws std::bad_alloc if out of memory
   */
  x86_emitter& emit_movsb() {
    return emit(0xA4);
  }

  /**
   * Emits a one-byte `MOVSW` instruction.
   *
   * @return `*this`
   * @throws std::bad_alloc if out of memory
   */
  x86_emitter& emit_movsw() {
    return emit(0xA5);
  }

  /**
   * Emits a one-byte `MOVSD` instruction.
   *
   * @return `*this`
   * @throws std::bad_alloc if out of memory
   */
  x86_emitter& emit_movsd() {
    return emit(0xA5);
  }

  /**
   * Emits a one-byte `MOVSQ` instruction.
   *
   * @return `*this`
   * @throws std::bad_alloc if out of memory
   */
  x86_emitter& emit_movsq() {
    return emit(0xA5);
  }

  /**
   * Emits a one-byte `NOP` instruction.
   *
   * @return `*this`
   * @throws std::bad_alloc if out of memory
   */
  x86_emitter& emit_nop() {
    return emit(0x90);
  }

  /**
   * Emits a one-byte `OUTSB` instruction.
   *
   * @return `*this`
   * @throws std::bad_alloc if out of memory
   */
  x86_emitter& emit_outsb() {
    return emit(0x6E);
  }

  /**
   * Emits a one-byte `OUTSW` instruction.
   *
   * @return `*this`
   * @throws std::bad_alloc if out of memory
   */
  x86_emitter& emit_outsw() {
    return emit(0x6F);
  }

  /**
   * Emits a one-byte `OUTSD` instruction.
   *
   * @return `*this`
   * @throws std::bad_alloc if out of memory
   */
  x86_emitter& emit_outsd() {
    return emit(0x6F);
  }

  /**
   * Emits a one-byte `POPA` instruction.
   *
   * @return `*this`
   * @throws std::bad_alloc if out of memory
   */
  x86_emitter& emit_popa() {
    return emit(0x61);
  }

  /**
   * Emits a one-byte `POPAD` instruction.
   *
   * @return `*this`
   * @throws std::bad_alloc if out of memory
   */
  x86_emitter& emit_popad() {
    return emit(0x61);
  }

  /**
   * Emits a one-byte `POPF` instruction.
   *
   * @return `*this`
   * @throws std::bad_alloc if out of memory
   */
  x86_emitter& emit_popf() {
    return emit(0x9D);
  }

  /**
   * Emits a one-byte `POPFD` instruction.
   *
   * @return `*this`
   * @throws std::bad_alloc if out of memory
   */
  x86_emitter& emit_popfd() {
    return emit(0x9D);
  }

  /**
   * Emits a one-byte `POPFQ` instruction.
   *
   * @return `*this`
   * @throws std::bad_alloc if out of memory
   */
  x86_emitter& emit_popfq() {
    return emit(0x9D);
  }

  /**
   * Emits a one-byte `PUSHA` instruction.
   *
   * @return `*this`
   * @throws std::bad_alloc if out of memory
   */
  x86_emitter& emit_pusha() {
    return emit(0x60);
  }

  /**
   * Emits a one-byte `PUSHAD` instruction.
   *
   * @return `*this`
   * @throws std::bad_alloc if out of memory
   */
  x86_emitter& emit_pushad() {
    return emit(0x60);
  }

  /**
   * Emits a one-byte `PUSHF` instruction.
   *
   * @return `*this`
   * @throws std::bad_alloc if out of memory
   */
  x86_emitter& emit_pushf() {
    return emit(0x9C);
  }

  /**
   * Emits a one-byte `PUSHFD` instruction.
   *
   * @return `*this`
   * @throws std::bad_alloc if out of memory
   */
  x86_emitter& emit_pushfd() {
    return emit(0x9C);
  }

  /**
   * Emits a one-byte `PUSHFQ` instruction.
   *
   * @return `*this`
   * @throws std::bad_alloc if out of memory
   */
  x86_emitter& emit_pushfq() {
    return emit(0x9C);
  }

  /**
   * Emits a one-byte `RET` instruction.
   *
   * @return `*this`
   * @throws std::bad_alloc if out of memory
   */
  x86_emitter& emit_ret() {
    return emit(0xC3);
  }

  /**
   * Emits a one-byte `RETF` instruction.
   *
   * @return `*this`
   * @throws std::bad_alloc if out of memory
   */
  x86_emitter& emit_retf() {
    return emit(0xCB);
  }

  /**
   * Emits a one-byte `SAHF` instruction.
   *
   * @return `*this`
   * @throws std::bad_alloc if out of memory
   */
  x86_emitter& emit_sahf() {
    return emit(0x9E);
  }

  /**
   * Emits a one-byte `SCASB` instruction.
   *
   * @return `*this`
   * @throws std::bad_alloc if out of memory
   */
  x86_emitter& emit_scasb() {
    return emit(0xAE);
  }

  /**
   * Emits a one-byte `SCASW` instruction.
   *
   * @return `*this`
   * @throws std::bad_alloc if out of memory
   */
  x86_emitter& emit_scasw() {
    return emit(0xAF);
  }

  /**
   * Emits a one-byte `SCASD` instruction.
   *
   * @return `*this`
   * @throws std::bad_alloc if out of memory
   */
  x86_emitter& emit_scasd() {
    return emit(0xAF);
  }

  /**
   * Emits a one-byte `SCASQ` instruction.
   *
   * @return `*this`
   * @throws std::bad_alloc if out of memory
   */
  x86_emitter& emit_scasq() {
    return emit(0xAF);
  }

  /**
   * Emits a one-byte `STC` instruction.
   *
   * @return `*this`
   * @throws std::bad_alloc if out of memory
   */
  x86_emitter& emit_stc() {
    return emit(0xF9);
  }

  /**
   * Emits a one-byte `STD` instruction.
   *
   * @return `*this`
   * @throws std::bad_alloc if out of memory
   */
  x86_emitter& emit_std() {
    return emit(0xFD);
  }

  /**
   * Emits a one-byte `STOSB` instruction.
   *
   * @return `*this`
   * @throws std::bad_alloc if out of memory
   */
  x86_emitter& emit_stosb() {
    return emit(0xAA);
  }

  /**
   * Emits a one-byte `STOSW` instruction.
   *
   * @return `*this`
   * @throws std::bad_alloc if out of memory
   */
  x86_emitter& emit_stosw() {
    return emit(0xAB);
  }

  /**
   * Emits a one-byte `STOSD` instruction.
   *
   * @return `*this`
   * @throws std::bad_alloc if out of memory
   */
  x86_emitter& emit_stosd() {
    return emit(0xAB);
  }

  /**
   * Emits a one-byte `STOSQ` instruction.
   *
   * @return `*this`
   * @throws std::bad_alloc if out of memory
   */
  x86_emitter& emit_stosq() {
    return emit(0xAB);
  }

  /**
   * Emits a one-byte `XLATB` instruction.
   *
   * @return `*this`
   * @throws std::bad_alloc if out of memory
   */
  x86_emitter& emit_xlatb() {
    return emit(0xD7);
  }
};

#endif /* MACHINERY_ARCH_X86_EMITTER_H */
