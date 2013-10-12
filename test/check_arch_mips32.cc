/* This is free and unencumbered software released into the public domain. */

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#define BOOST_TEST_MODULE arch_mips32
#include <boost/test/unit_test.hpp>

#include <machinery.h>
#include <machinery/arch/mips32.h>
#include <machinery/util/buffer.h>

#include <cstdio> /* for std::sprintf() */

using namespace machinery::arch;
using namespace machinery::arch::mips32;
using namespace machinery::util;

BOOST_AUTO_TEST_CASE(nop) {
  // TODO
}
