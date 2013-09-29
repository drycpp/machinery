/* This is free and unencumbered software released into the public domain. */

#ifndef MACHINERY_UTIL_BUFFER_H
#define MACHINERY_UTIL_BUFFER_H

/**
 * @file
 *
 * Buffer utilities.
 */

#include <cstddef> /* for std::size_t */
#include <cstdint> /* for std::uint8_t */
#include <vector>  /* for std::vector */
#include <initializer_list>

namespace machinery {
  namespace util {
    class buffer;
    class appendable_buffer;
    class executable_buffer;
  }
}

/**
 * Base class for buffers.
 */
class machinery::util::buffer {};

/**
 * A buffer for code generation.
 */
class machinery::util::appendable_buffer : public machinery::util::buffer {
  std::vector<std::uint8_t> _bytes;

public:
  /**
   * Default constructor.
   */
  appendable_buffer() noexcept = default;

  /**
   * Copy constructor.
   */
  appendable_buffer(const appendable_buffer& other) = default;

  /**
   * Move constructor.
   */
  appendable_buffer(appendable_buffer&& other) noexcept = default;

  /**
   * Destructor.
   */
  ~appendable_buffer() noexcept = default;

  /**
   * Copy assignment operator.
   */
  appendable_buffer& operator=(const appendable_buffer& other) = default;

  /**
   * Move assignment operator.
   */
  appendable_buffer& operator=(appendable_buffer&& other) noexcept = default;

  /**
   * Returns the current byte size of this buffer.
   */
  std::size_t size() const noexcept {
    return _bytes.size();
  }

  /**
   * Returns a pointer to the byte data in this buffer.
   */
  const std::uint8_t* data() const noexcept {
    return _bytes.data();
  }

  /**
   * Appends the given byte to the end of this buffer.
   *
   * @throws std::bad_alloc if out of memory
   */
  appendable_buffer& append(const std::uint8_t byte) {
    _bytes.emplace_back(byte);
    return *this;
  }

  /**
   * Appends the given bytes to the end of this buffer.
   *
   * @throws std::bad_alloc if out of memory
   */
  appendable_buffer& append(const std::initializer_list<std::uint8_t> bytes) {
    _bytes.insert(_bytes.end(), bytes);
    return *this;
  }
};

#endif /* MACHINERY_UTIL_BUFFER_H */
