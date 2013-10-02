/* This is free and unencumbered software released into the public domain. */

#ifndef MACHINERY_BITS_WORD_H
#define MACHINERY_BITS_WORD_H

/**
 * @file
 *
 * Machine word sizes.
 *
 * @see http://en.wikipedia.org/wiki/Word_(computer_architecture)
 */

#include <cstdint> /* for std::int*_t, std::uint*_t */

namespace machinery {
  namespace bits {
    union word8;
    union word16;
    union word32;
    union word64;
  }
}

/**
 * 8-bit machine word.
 */
union machinery::bits::word8 final {
  std::int8_t  s8;
  std::uint8_t u8;

  /**
   * Constructor.
   *
   * @param value a signed integer
   */
  explicit word8(const std::int8_t value) noexcept
    : s8(value) {}

  /**
   * Constructor.
   *
   * @param value an unsigned integer
   */
  explicit word8(const std::uint8_t value) noexcept
    : u8(value) {}
};

/**
 * 16-bit machine word.
 */
union machinery::bits::word16 final {
  std::int16_t  s16;
  std::uint16_t u16;
  std::int8_t   s8[2];
  std::uint8_t  u8[2];

  /**
   * Constructor.
   *
   * @param value a signed integer
   */
  explicit word16(const std::int16_t value) noexcept
    : s16(value) {}

  /**
   * Constructor.
   *
   * @param value an unsigned integer
   */
  explicit word16(const std::uint16_t value) noexcept
    : u16(value) {}
};

/**
 * 32-bit machine word.
 */
union machinery::bits::word32 final {
  std::int32_t  s32;
  std::uint32_t u32;
  std::int8_t   s8[4];
  std::uint8_t  u8[4];

  /**
   * Constructor.
   *
   * @param value a signed integer
   */
  explicit word32(const std::int32_t value) noexcept
    : s32(value) {}

  /**
   * Constructor.
   *
   * @param value an unsigned integer
   */
  explicit word32(const std::uint32_t value) noexcept
    : u32(value) {}
};

/**
 * 64-bit machine word.
 */
union machinery::bits::word64 final {
  std::int64_t  s64;
  std::uint64_t u64;
  std::int8_t   s8[8];
  std::uint8_t  u8[8];

  /**
   * Constructor.
   *
   * @param value a signed integer
   */
  explicit word64(const std::int64_t value) noexcept
    : s64(value) {}

  /**
   * Constructor.
   *
   * @param value an unsigned integer
   */
  explicit word64(const std::uint64_t value) noexcept
    : u64(value) {}
};

#endif /* MACHINERY_BITS_WORD_H */
