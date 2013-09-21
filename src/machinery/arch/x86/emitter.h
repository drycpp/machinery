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
   * Emits a 1-byte instruction.
   *
   * @throws std::bad_alloc if out of memory
   */
  inline x86_emitter& emit(const x86_opcode opcode) {
    _buffer.push_back(opcode);
    return *this;
  }

  /**
   * Emits a 2-byte instruction.
   *
   * @throws std::bad_alloc if out of memory
   */
  inline x86_emitter& emit(const x86_opcode opcode,
                           const x86_opcode opcode2) {
    _buffer.push_back(opcode);
    _buffer.push_back(opcode2);
    return *this;
  }

  /**
   * Emits a 3-byte instruction.
   *
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
};

#endif /* MACHINERY_ARCH_X86_EMITTER_H */
