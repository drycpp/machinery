/* This is free and unencumbered software released into the public domain. */

#ifndef MACHINERY_UTIL_BUFFER_H
#define MACHINERY_UTIL_BUFFER_H

/**
 * @file
 *
 * Buffer utilities.
 */

#include <cstddef>          /* for std::size_t */
#include <cstdint>          /* for std::uint8_t */
#include <cstdio>           /* for FILE */
#include <initializer_list> /* for std::initializer_list */
#include <stdexcept>        /* for std::logic_error */
#include <vector>           /* for std::vector */

namespace machinery {
  namespace util {
    class buffer;
    class appendable_buffer;
    class executable_buffer;
    class persistent_buffer;
  }
}

/**
 * Base class for buffers.
 */
class machinery::util::buffer {
protected:
  /**
   * Default constructor.
   */
  buffer() noexcept = default;

public:
  /**
   * Returns the current byte capacity of this buffer.
   */
  std::size_t capacity() const;

  /**
   * Returns the current byte size of this buffer.
   */
  std::size_t size() const;

  /**
   * Returns a pointer to the byte data in this buffer.
   */
  const std::uint8_t* data() const {
    throw std::logic_error("no data pointer available for this buffer type");
  }

  /**
   * Appends the given byte to the end of this buffer.
   *
   * @throws std::bad_alloc if out of memory
   */
  buffer& append(const std::uint8_t byte);

  /**
   * Appends the given bytes to the end of this buffer.
   *
   * @throws std::bad_alloc if out of memory
   */
  buffer& append(const std::initializer_list<std::uint8_t> bytes);
};

/**
 * A buffer for code generation.
 */
class machinery::util::appendable_buffer : public machinery::util::buffer {
  std::vector<std::uint8_t> _bytes;

public:
  /**
   * Default constructor.
   */
  appendable_buffer() = default;

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
   * Returns the current byte capacity of this buffer.
   */
  std::size_t capacity() const noexcept {
    return _bytes.capacity();
  }

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

/**
 * A buffer for code generation and execution.
 *
 * @note Instances of this class are movable, but not copyable.
 */
class machinery::util::executable_buffer : public machinery::util::buffer {
  std::uint8_t* _data {nullptr};
  std::size_t _size {0};
  std::size_t _capacity {0};

public:
  /**
   * Default constructor.
   *
   * @throws std::system_error in case of error
   */
  executable_buffer();

  /**
   * Constructor.
   *
   * @throws std::system_error in case of error
   */
  executable_buffer(std::size_t capacity);

  /**
   * Copy constructor.
   *
   * @throws std::system_error in case of error
   */
  executable_buffer(const appendable_buffer& buffer);

  /**
   * Copy constructor.
   *
   * @throws std::system_error in case of error
   */
  executable_buffer(const executable_buffer& other);

  /**
   * Move constructor.
   */
  executable_buffer(executable_buffer&& other) noexcept = default;

  /**
   * Destructor.
   */
  ~executable_buffer() noexcept;

  /**
   * Copy assignment operator.
   */
  executable_buffer& operator=(const executable_buffer& other) = delete;

  /**
   * Move assignment operator.
   */
  executable_buffer& operator=(executable_buffer&& other) noexcept = default;

  /**
   * Returns the current byte capacity of this buffer.
   */
  std::size_t capacity() const noexcept {
    return _capacity;
  }

  /**
   * Returns the current byte size of this buffer.
   */
  std::size_t size() const noexcept {
    return _size;
  }

  /**
   * Returns a pointer to the byte data in this buffer.
   */
  const std::uint8_t* data() const noexcept {
    return _data;
  }

  /**
   * Appends the given byte to the end of this buffer.
   *
   * @post Invalidates any pointers previously returned by `data()`.
   * @throws std::bad_alloc if out of memory
   */
  executable_buffer& append(const std::uint8_t byte) {
    if (_size == _capacity) {
      grow();
    }
    _data[_size++] = byte;
    return *this;
  }

  /**
   * Appends the given bytes to the end of this buffer.
   *
   * @post Invalidates any pointers previously returned by `data()`.
   * @throws std::bad_alloc if out of memory
   */
  executable_buffer& append(const std::initializer_list<std::uint8_t> bytes) {
    for (const auto byte : bytes) {
      append(byte);
    }
    return *this;
  }

  /**
   * Executes the code in this buffer.
   *
   * @pre  The generated code must include a return instruction.
   * @post Processor registers may be clobbered.
   */
  void execute() const {
    reinterpret_cast<void (*)()>(_data)();
  }

  /**
   * Executes the code in this buffer, returning a value of type `T`.
   *
   * @return a value of type `T`
   * @pre  The generated code must include a return instruction.
   * @post Processor registers may be clobbered.
   * @note How to return a value from the generated code is entirely
   *       dependent on particulars of the architecture and calling
   *       convention. Please refer to your platform documentation.
   */
  template <typename T>
  T execute() const {
    return reinterpret_cast<T (*)()>(_data)();
  }

protected:
  /**
   * Grows the size of this buffer.
   *
   * @throws std::bad_alloc if out of memory
   * @throws std::system_error in case of another error
   */
  void grow();
};

/**
 * A buffer for code generation into a file stream.
 *
 * @note Instances of this class are movable, but not copyable.
 */
class machinery::util::persistent_buffer : public machinery::util::buffer {
  FILE* _stream;
  std::size_t _begin_offset;

public:
  /**
   * Default constructor.
   */
  persistent_buffer() noexcept = delete;

  /**
   * Default constructor.
   *
   * @throws std::invalid_argument if `stream` is `nullptr`
   * @throws std::system_error in case of error
   */
  persistent_buffer(FILE* stream);

  /**
   * Copy constructor.
   */
  persistent_buffer(const persistent_buffer& other) = delete;

  /**
   * Move constructor.
   */
  persistent_buffer(persistent_buffer&& other) noexcept = default;

  /**
   * Destructor.
   */
  ~persistent_buffer() noexcept;

  /**
   * Copy assignment operator.
   */
  persistent_buffer& operator=(const persistent_buffer& other) = delete;

  /**
   * Move assignment operator.
   */
  persistent_buffer& operator=(persistent_buffer&& other) noexcept = default;

  /**
   * Returns the current byte capacity of this buffer.
   *
   * @throws std::system_error in case of error
   */
  std::size_t capacity() const {
    return size();
  }

  /**
   * Returns the current byte size of this buffer.
   *
   * @throws std::system_error in case of error
   */
  std::size_t size() const;

  /**
   * Returns the current file offset.
   *
   * @throws std::system_error in case of error
   */
  std::size_t offset() const;

  /**
   * Appends the given byte to the end of this buffer.
   *
   * @throws std::system_error in case of error
   */
  persistent_buffer& append(const std::uint8_t byte);

  /**
   * Appends the given bytes to the end of this buffer.
   *
   * @throws std::system_error in case of error
   */
  persistent_buffer& append(const std::initializer_list<std::uint8_t> bytes) {
    for (const auto byte : bytes) {
      append(byte);
    }
    return *this;
  }
};

#endif /* MACHINERY_UTIL_BUFFER_H */
