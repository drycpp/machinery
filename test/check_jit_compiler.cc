/* This is free and unencumbered software released into the public domain. */

#define BOOST_TEST_MODULE jit
#include <boost/test/unit_test.hpp>

#include <machinery/jit.h>
#include <machinery/util/buffer.h>

#include <cstdio> /* for std::sprintf() */

using namespace machinery::jit;
using namespace machinery::util;

BOOST_AUTO_TEST_CASE(for_unknown) {
  BOOST_CHECK_THROW(compiler_for("unknown"), std::invalid_argument);
}

#ifndef DISABLE_ARM
BOOST_AUTO_TEST_CASE(for_armv8_aarch64) {
  BOOST_CHECK(compiler_for("armv8-aarch64"));
  BOOST_CHECK(compiler_for_armv8_aarch64());
}
#endif

#ifndef DISABLE_X86
BOOST_AUTO_TEST_CASE(for_x86_64) {
  BOOST_CHECK(compiler_for("x86-64"));
  BOOST_CHECK(compiler_for_x86_64());
}
#endif
