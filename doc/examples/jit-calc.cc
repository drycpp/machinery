/* This is free and unencumbered software released into the public domain. */

#include <machinery.h>
#include <machinery/arch/x86.h>
#include <machinery/util/buffer.h>

#include <cstdio>  /* for std::fwrite() */
#include <cstdlib> /* for std::atoi() */

using namespace machinery::arch::x86;
using namespace machinery::util;

int
main(int argc, char* argv[]) {
  appendable_buffer buffer;
  emitter code(buffer);

  /* Clear the EAX register: */
  code.emit_mov(reg32::EAX, imm32{0});

  /* For each command-line argument: */
  for (int i = 1; i < argc; i++) {
    /* Convert the argument to an integer: */
    const int arg = std::atoi(argv[i]);

    /* Add the integer argument to EAX: */
    code.emit_add(imm32{arg});
  }

  /* Return to the caller: */
  code.emit_ret();

#if 1
  std::fwrite(buffer.data(), buffer.size(), 1, stdout);
#endif

  // TODO: execute the code buffer and print out the result.

  return 0;
}
