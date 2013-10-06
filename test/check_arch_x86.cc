/* This is free and unencumbered software released into the public domain. */

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#define BOOST_TEST_MODULE arch_x86
#include <boost/test/unit_test.hpp>

#include <machinery.h>
#include <machinery/arch/x86.h>
#include <machinery/util/buffer.h>

#include <cstdio> /* for std::sprintf() */

using namespace machinery::arch;
using namespace machinery::arch::x86;
using namespace machinery::util;

static appendable_buffer _buffer;

static x86_emitter<decltype(_buffer)>
emit() {
  _buffer.clear();
  return x86_emitter<decltype(_buffer)>(_buffer);
}

static const char*
s(const x86_emitter<decltype(_buffer)>&) {
  static char string[4096];
  for (auto i = 0UL; i < _buffer.size(); i++) {
    std::sprintf(string + i * 2, "%02X", _buffer.data()[i]);
  }
  return string;
}

BOOST_AUTO_TEST_CASE(add_al_imm8) {
  BOOST_CHECK_EQUAL(s(emit().add(imm8{0x12})), "0412");
}

BOOST_AUTO_TEST_CASE(add_ax_imm16) {
  BOOST_CHECK_EQUAL(s(emit().add(imm16{0x1234})), "66053412");
}

BOOST_AUTO_TEST_CASE(add_eax_imm32) {
  BOOST_CHECK_EQUAL(s(emit().add(imm32{0x12345678})), "0578563412");
}

BOOST_AUTO_TEST_CASE(add_rax_imm32) {
  BOOST_CHECK_EQUAL(s(emit().add(imm64{0x12345678})), "480578563412");
}

BOOST_AUTO_TEST_CASE(leave) {
  BOOST_CHECK_EQUAL(s(emit().leave()), "C9");
}

BOOST_AUTO_TEST_CASE(mov_reg64_reg64) {
  BOOST_CHECK_EQUAL(s(emit().mov(reg64::rbp, reg64::rsp)), "4889E5");
}

BOOST_AUTO_TEST_CASE(nop) {
  BOOST_CHECK_EQUAL(s(emit().nop()), "90");
}

BOOST_AUTO_TEST_CASE(pop_rbp) {
  BOOST_CHECK_EQUAL(s(emit().pop(reg64::rbp)), "5D");
}

BOOST_AUTO_TEST_CASE(push_rbp) {
  BOOST_CHECK_EQUAL(s(emit().push(reg64::rbp)), "55");
}

BOOST_AUTO_TEST_CASE(ret) {
  BOOST_CHECK_EQUAL(s(emit().ret()), "C3");
}

BOOST_AUTO_TEST_CASE(xor_al_al) {
  //BOOST_CHECK_EQUAL(s(emit().xor_(reg8::al, reg8::al)), "30C0");
}

BOOST_AUTO_TEST_CASE(xor_ax_ax) {
  //BOOST_CHECK_EQUAL(s(emit().xor_(reg16::ax, reg16::ax)), "6631C0");
}

BOOST_AUTO_TEST_CASE(xor_eax_eax) {
  //BOOST_CHECK_EQUAL(s(emit().xor_(reg32::eax, reg32::eax)), "31C0");
}

BOOST_AUTO_TEST_CASE(xor_rax_rax) {
  //BOOST_CHECK_EQUAL(s(emit().xor_(reg64::rax, reg64::rax)), "4831C0");
}
