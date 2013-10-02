/* This is free and unencumbered software released into the public domain. */

#ifndef MACHINERY_JIT_COMPILER_H
#define MACHINERY_JIT_COMPILER_H

/**
 * @file
 *
 * Target-independent just-in-time (JIT) compiler.
 */

#include "../util/buffer.h"

#include <cstddef> /* for std::size_t */
#include <memory>  /* for std::unique_ptr */

namespace machinery {
  namespace jit {
    class compiler;

    /**
     * Returns a JIT compiler for the given target architecture.
     *
     * @param target either "x86-64" or "armv8-aarch64"
     * @throws std::invalid_argument if `target` is unknown
     */
    std::unique_ptr<compiler> compiler_for(const char* target);

    /**
     * Returns a JIT compiler targeting the ARMv8 AArch64 architecture.
     */
    std::unique_ptr<compiler> compiler_for_armv8_aarch64();

    /**
     * Returns a JIT compiler targeting the x86-64 architecture.
     */
    std::unique_ptr<compiler> compiler_for_x86_64();
  }
}

/**
 * Base class for just-in-time (JIT) compiler implementations.
 *
 * @note Instances of this class are not movable or copyable.
 */
class machinery::jit::compiler {
protected:
  using buffer = machinery::util::appendable_buffer;

  buffer _buffer;

  /**
   * Default constructor.
   */
  compiler() = default;

public:
  /**
   * Copy constructor.
   */
  compiler(const compiler& other) noexcept = delete;

  /**
   * Move constructor.
   */
  compiler(compiler&& other) noexcept = delete;

  /**
   * Destructor.
   */
  virtual ~compiler() noexcept;

  /**
   * Copy assignment operator.
   */
  compiler& operator=(const compiler& other) noexcept = delete;

  /**
   * Move assignment operator.
   */
  compiler& operator=(compiler&& other) noexcept = delete;

  /**
   * Emits a `NOP` instruction.
   */
  virtual compiler& nop() = 0;
};

#endif /* MACHINERY_JIT_COMPILER_H */
