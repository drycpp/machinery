/* This is free and unencumbered software released into the public domain. */

#define BOOST_TEST_MODULE arch_arm
#include <boost/test/unit_test.hpp>

#include <machinery.h>
#include <machinery/arch/arm.h>
#include <machinery/util/buffer.h>

#include <cstdio> /* for std::sprintf() */

using namespace machinery::arch;
using namespace machinery::arch::arm;
using namespace machinery::util;

static appendable_buffer _buffer;

static arm_emitter<decltype(_buffer)>
emit() {
  _buffer.clear();
  return arm_emitter<decltype(_buffer)>(_buffer);
}

static const char*
s(const arm_emitter<decltype(_buffer)>&) {
  static char string[4096];
  for (auto i = 0UL; i < _buffer.size(); i++) {
    std::sprintf(string + i * 2, "%02X", _buffer.data()[i]);
  }
  return string;
}

BOOST_AUTO_TEST_CASE(hint) {
  BOOST_CHECK_EQUAL(s(emit().hint()), "D503201F");
  BOOST_CHECK_EQUAL(s(emit().hint(0)), "D503201F");
  BOOST_CHECK_EQUAL(s(emit().hint(1)), "D503203F");
  BOOST_CHECK_EQUAL(s(emit().hint(2)), "D503205F");
  BOOST_CHECK_EQUAL(s(emit().hint(3)), "D503207F");
  BOOST_CHECK_EQUAL(s(emit().hint(4)), "D503209F");
  BOOST_CHECK_EQUAL(s(emit().hint(5)), "D50320BF");
}

BOOST_AUTO_TEST_CASE(nop) {
  BOOST_CHECK_EQUAL(s(emit().nop()), "D503201F");
}

BOOST_AUTO_TEST_CASE(sev) {
  BOOST_CHECK_EQUAL(s(emit().sev()), "D503209F");
}

BOOST_AUTO_TEST_CASE(sevl) {
  BOOST_CHECK_EQUAL(s(emit().sevl()), "D50320BF");
}

BOOST_AUTO_TEST_CASE(wfe) {
  BOOST_CHECK_EQUAL(s(emit().wfe()), "D503205F");
}

BOOST_AUTO_TEST_CASE(wfi) {
  BOOST_CHECK_EQUAL(s(emit().wfi()), "D503207F");
}

BOOST_AUTO_TEST_CASE(yield) {
  BOOST_CHECK_EQUAL(s(emit().yield()), "D503203F");
}
