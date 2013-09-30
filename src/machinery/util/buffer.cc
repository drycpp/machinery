/* This is free and unencumbered software released into the public domain. */

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include "buffer.h"

#include <algorithm>    /* for std::max() */
#include <cassert>      /* for assert() */
#include <cerrno>       /* for errno */
#include <cstdio>       /* for std::fputc(), std::ftell() */
#include <cstring>      /* for std::memcpy() */
#include <stdexcept>    /* for std::bad_alloc, std::invalid_argument */
#include <sys/mman.h>   /* for mmap(), munmap(), mremap() */
#include <system_error> /* for std::system_error */
#include <unistd.h>     /* for sysconf() */

using namespace machinery::util;

static const int mmap_prot  = PROT_READ | PROT_WRITE | PROT_EXEC;
static const int mmap_flags = MAP_PRIVATE | MAP_ANON;
static const std::size_t mmap_size = sysconf(_SC_PAGESIZE);

executable_buffer::executable_buffer()
  : executable_buffer(mmap_size) {}

executable_buffer::executable_buffer(const std::size_t capacity)
  : _data(nullptr),
    _size(0),
    _capacity(std::max(capacity, mmap_size)) {

  void* const addr = ::mmap(nullptr, _capacity, mmap_prot, mmap_flags, -1, 0);
  if (addr == MAP_FAILED) {
    switch (errno) {
      case ENOMEM: /* Cannot allocate memory in kernel */
        throw std::bad_alloc();
      default:
        assert(errno != EBADF);
        throw std::system_error(errno, std::system_category());
    }
  }

  _data = reinterpret_cast<std::uint8_t*>(addr);
}

executable_buffer::executable_buffer(const executable_buffer& buffer)
  : executable_buffer(buffer.size()) {
  std::memcpy(_data, buffer.data(), buffer.size());
}

executable_buffer::executable_buffer(const appendable_buffer& buffer)
  : executable_buffer(buffer.size()) {
  std::memcpy(_data, buffer.data(), buffer.size());
}

executable_buffer::~executable_buffer() noexcept {
  if (_data) {
    if (::munmap(reinterpret_cast<void*>(_data), _size) == -1) {
      /* Ignore any errors from munmap(). */
    }
    _data = nullptr;
    _size = _capacity = 0;
  }
}

void
executable_buffer::grow() {
#ifdef __linux__
  // TODO: use mremap()
#else
  // TODO: use mmap()
#endif
  throw std::system_error(ENOSYS, std::system_category());
}

persistent_buffer::persistent_buffer(FILE* const stream)
  : _stream(stream),
    _begin_offset(0) {
  if (!stream) {
    throw std::invalid_argument("stream cannot be nullptr");
  }
  _begin_offset = offset();
}

persistent_buffer::~persistent_buffer() noexcept {
  if (_stream) {
    _stream = nullptr;
  }
}

std::size_t
persistent_buffer::size() const {
  return offset() - _begin_offset;
}

std::size_t
persistent_buffer::offset() const {
  long offset;
  if ((offset = std::ftell(_stream)) == -1) {
    throw std::system_error(errno, std::system_category());
  }
  return static_cast<std::size_t>(offset);
}

persistent_buffer&
persistent_buffer::append(const std::uint8_t byte) {
  if (std::fputc(static_cast<int>(byte), _stream) == EOF) {
    throw std::system_error(errno, std::system_category());
  }
  return *this;
}
