/* This is free and unencumbered software released into the public domain. */

#include <machinery.h>
#include <machinery/arch/x86.h>
#include <machinery/util/buffer.h>

#include <cstdio>  /* for stdout, std::printf() */
#include <cstdlib> /* for std::atoi() */

using namespace machinery::arch;
using namespace machinery::arch::x86;
using namespace machinery::util;

int
main(int argc, char* argv[]) {
  //persistent_buffer buffer(stdout);
  appendable_buffer buffer;
  x86_emitter<decltype(buffer)> code(buffer);

  /* Function prolog: */
  code.emit_push(reg64::rbp);
  code.emit_mov(reg64::rbp, reg64::rsp);

  /* Clear the RAX register: */
  code.emit_mov(reg64::rax, imm64{0});
  //code.emit_xor(reg64::rax, reg64::rax); // TODO

  /* For each command-line argument: */
  for (int i = 1; i < argc; i++) {
    /* Convert the argument to an integer: */
    const int arg = std::atoi(argv[i]);

    /* Add the integer argument to RAX: */
    code.emit_add(imm32{static_cast<std::uint32_t>(arg)});
  }

  /* Function epilog: */
  code.emit_pop(reg64::rbp);
  code.emit_ret();

#if 1
  /* Execute the code buffer and print out the result: */
  executable_buffer exec(buffer);
  std::printf("%d\n", exec.execute<std::int32_t>());
#endif

  return 0;
}
