/* This is free and unencumbered software released into the public domain. */

#ifndef MACHINERY_JIT_COMPILER_H
#define MACHINERY_JIT_COMPILER_H

/**
 * @file
 */

#include <cstddef> /* for std::size_t */

namespace machinery {
  namespace jit {
    class compiler;
  }
}

/**
 * Target-independent just-in-time (JIT) compiler.
 *
 * @note Instances of this class are not movable or copyable.
 */
class machinery::jit::compiler {
protected:
  /**
   * Default constructor.
   */
  compiler() noexcept = default;

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
  virtual ~compiler() noexcept = 0;

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
