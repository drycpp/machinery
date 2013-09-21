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
};

#endif /* MACHINERY_ARCH_X86_EMITTER_H */
