/* This is free and unencumbered software released into the public domain. */

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include "buffer.h"

#include <cassert>      /* for assert() */
#include <cerrno>       /* for errno */
#include <stdexcept>    /* for std::bad_alloc */
#include <sys/mman.h>   /* for mmap(), munmap(), mremap() */
#include <system_error> /* for std::system_error */
#include <unistd.h>     /* for sysconf() */

using namespace machinery::util;

static const int mmap_prot  = PROT_READ | PROT_WRITE | PROT_EXEC;
static const int mmap_flags = MAP_PRIVATE | MAP_ANON;
static const std::size_t mmap_size = sysconf(_SC_PAGESIZE);

executable_buffer::executable_buffer()
  : _data(nullptr),
    _size(0),
    _capacity(mmap_size) {

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
