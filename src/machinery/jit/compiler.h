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
     * @param target either "x86-64", "armv8-aarch64", or "mips32"
     * @throws std::invalid_argument if `target` is unknown
     */
    std::unique_ptr<compiler> compiler_for(const char* target);

    /**
     * Returns a JIT compiler targeting the ARMv8 AArch64 architecture.
     */
    std::unique_ptr<compiler> compiler_for_armv8_aarch64();

    /**
     * Returns a JIT compiler targeting the MIPS32 architecture.
     */
    std::unique_ptr<compiler> compiler_for_mips32();

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
   * @name Control Instructions
   */

  /**@{*/

  /**
   * Emits an `ENTER` (enter stack frame) instruction.
   */
  virtual compiler& enter() = 0;

  /**
   * Emits a `JMP` (jump) instruction.
   */
  virtual compiler& jmp(...) = 0;

  /**
   * Emits a `LEAVE` (leave stack frame) instruction.
   */
  virtual compiler& leave() = 0;

  /**
   * Emits a `RET` (return) instruction.
   */
  virtual compiler& ret() = 0;

  /**@}*/

  /**
   * @name Basic Instructions
   */

  /**@{*/

  /**
   * Emits an `ABS` (absolute value) instruction.
   */
  virtual compiler& abs(...) = 0;

  /**
   * Emits an `ADD` (add) instruction.
   */
  virtual compiler& add(...) = 0;

  /**
   * Emits an `AND` (bitwise AND) instruction.
   */
  virtual compiler& and_(...) = 0;

  /**
   * Emits a `CLZ` (count leading zeroes) instruction.
   */
  virtual compiler& clz(...) = 0;

  /**
   * Emits a `CMP` (compare) instruction.
   */
  virtual compiler& cmp(...) = 0;

  /**
   * Emits a `DEC` (decrement) instruction.
   */
  virtual compiler& dec(...) = 0;

  /**
   * Emits a `DIV` (divide) instruction.
   */
  virtual compiler& div(...) = 0;

  /**
   * Emits an `INC` (increment) instruction.
   */
  virtual compiler& inc(...) = 0;

  /**
   * Emits a `MOV` (move) instruction.
   */
  virtual compiler& mov(...) = 0;

  /**
   * Emits a `MUL` (multiply) instruction.
   */
  virtual compiler& mul(...) = 0;

  /**
   * Emits a `NAND` (bitwise NAND) instruction.
   */
  virtual compiler& nand(...) = 0;

  /**
   * Emits a `NEG` (negate) instruction.
   */
  virtual compiler& neg(...) = 0;

  /**
   * Emits a `NOP` (no operation) instruction.
   */
  virtual compiler& nop() = 0;

  /**
   * Emits a `NOR` (bitwise NOR) instruction.
   */
  virtual compiler& nor(...) = 0;

  /**
   * Emits a `NOT` (bitwise NOT) instruction.
   */
  virtual compiler& not_(...) = 0;

  /**
   * Emits an `OR` (bitwise OR) instruction.
   */
  virtual compiler& or_(...) = 0;

  /**
   * Emits a `POW` (power) instruction.
   */
  virtual compiler& pow(...) = 0;

  /**
   * Emits a `REM` (remainder) instruction.
   */
  virtual compiler& rem(...) = 0;

  /**
   * Emits an `SHL` (shift left) instruction.
   */
  virtual compiler& shl(...) = 0;

  /**
   * Emits an `SHR` (shift right) instruction.
   */
  virtual compiler& shr(...) = 0;

  /**
   * Emits a `SUB` (subtract) instruction.
   */
  virtual compiler& sub(...) = 0;

  /**
   * Emits a `XOR` (exclusive-or) instruction.
   */
  virtual compiler& xor_(...) = 0;

  /**@}*/
};

#endif /* MACHINERY_JIT_COMPILER_H */
