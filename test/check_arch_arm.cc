/* This is free and unencumbered software released into the public domain. */

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

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
  BOOST_CHECK_EQUAL(s(emit().hint()), "1F2003D5");
  BOOST_CHECK_EQUAL(s(emit().hint(0)), "1F2003D5");
  BOOST_CHECK_EQUAL(s(emit().hint(1)), "3F2003D5");
  BOOST_CHECK_EQUAL(s(emit().hint(2)), "5F2003D5");
  BOOST_CHECK_EQUAL(s(emit().hint(3)), "7F2003D5");
  BOOST_CHECK_EQUAL(s(emit().hint(4)), "9F2003D5");
  BOOST_CHECK_EQUAL(s(emit().hint(5)), "BF2003D5");
}

BOOST_AUTO_TEST_CASE(nop) {
  BOOST_CHECK_EQUAL(s(emit().nop()), "1F2003D5");
}

BOOST_AUTO_TEST_CASE(sev) {
  BOOST_CHECK_EQUAL(s(emit().sev()), "9F2003D5");
}

BOOST_AUTO_TEST_CASE(sevl) {
  BOOST_CHECK_EQUAL(s(emit().sevl()), "BF2003D5");
}

BOOST_AUTO_TEST_CASE(wfe) {
  BOOST_CHECK_EQUAL(s(emit().wfe()), "5F2003D5");
}

BOOST_AUTO_TEST_CASE(wfi) {
  BOOST_CHECK_EQUAL(s(emit().wfi()), "7F2003D5");
}

BOOST_AUTO_TEST_CASE(yield) {
  BOOST_CHECK_EQUAL(s(emit().yield()), "3F2003D5");
}
