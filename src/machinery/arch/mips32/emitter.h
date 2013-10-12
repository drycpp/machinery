/* This is free and unencumbered software released into the public domain. */

#ifndef MACHINERY_ARCH_MIPS32_EMITTER_H
#define MACHINERY_ARCH_MIPS32_EMITTER_H

/**
 * @file
 *
 * MIPS32 machine code emission.
 */

#include "encoding.h"

#include <cstddef>   /* for std::size_t */
#include <cstdint>   /* for std::uint8_t */
#include <stdexcept> /* for std::runtime_error */

namespace machinery {
  namespace arch {
    template<class Buffer> class mips32_emitter;
  }
}

/**
 * MIPS32 machine code emitter.
 *
 * @note Instances of this class are movable, but not copyable.
 */
template <class Buffer>
class machinery::arch::mips32_emitter {
  Buffer& _buffer;
  std::size_t _buffer_start;

public:
  /**
   * Default constructor.
   */
  mips32_emitter() noexcept = delete;

  /**
   * Constructor.
   *
   * @param buffer the output buffer
   */
  mips32_emitter(Buffer& buffer) noexcept
    : _buffer(buffer),
      _buffer_start(buffer.size()) {}

  /**
   * Copy constructor.
   */
  mips32_emitter(const mips32_emitter& other) noexcept = delete;

  /**
   * Move constructor.
   */
  mips32_emitter(mips32_emitter&& other) noexcept = default;

  /**
   * Destructor.
   */
  ~mips32_emitter() noexcept = default;

  /**
   * Copy assignment operator.
   */
  mips32_emitter& operator=(const mips32_emitter& other) noexcept = delete;

  /**
   * Move assignment operator.
   */
  mips32_emitter& operator=(mips32_emitter&& other) noexcept = default;

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

#endif /* MACHINERY_ARCH_MIPS32_EMITTER_H */
