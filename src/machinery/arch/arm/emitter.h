/* This is free and unencumbered software released into the public domain. */

#ifndef MACHINERY_ARCH_ARM_EMITTER_H
#define MACHINERY_ARCH_ARM_EMITTER_H

/**
 * @file
 *
 * ARMv8 A64 machine code emission.
 */

#include "encoding.h"

#include <cstddef>   /* for std::size_t */
#include <cstdint>   /* for std::uint8_t */
#include <stdexcept> /* for std::runtime_error */

namespace machinery {
  namespace arch {
    template<class Buffer> class arm_emitter;
  }
}

/**
 * ARMv8 A64 machine code emitter.
 *
 * @note Instances of this class are movable, but not copyable.
 */
template <class Buffer>
class machinery::arch::arm_emitter {
  Buffer& _buffer;
  std::size_t _buffer_start;

public:
  /**
   * Default constructor.
   */
  arm_emitter() noexcept = delete;

  /**
   * Constructor.
   *
   * @param buffer the output buffer
   */
  arm_emitter(Buffer& buffer) noexcept
    : _buffer(buffer),
      _buffer_start(buffer.size()) {}

  /**
   * Copy constructor.
   */
  arm_emitter(const arm_emitter& other) noexcept = delete;

  /**
   * Move constructor.
   */
  arm_emitter(arm_emitter&& other) noexcept = default;

  /**
   * Destructor.
   */
  ~arm_emitter() noexcept = default;

  /**
   * Copy assignment operator.
   */
  arm_emitter& operator=(const arm_emitter& other) noexcept = delete;

  /**
   * Move assignment operator.
   */
  arm_emitter& operator=(arm_emitter&& other) noexcept = default;

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
};

#endif /* MACHINERY_ARCH_ARM_EMITTER_H */
