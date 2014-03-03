/* This is free and unencumbered software released into the public domain. */

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include "catch.hpp"

#include <machinery.h>
#include <machinery/arch/mips32.h>
#include <machinery/util/buffer.h>

#include <cstdio> /* for std::sprintf() */

using namespace machinery::arch;
using namespace machinery::arch::mips32;
using namespace machinery::util;

TEST_CASE("nop") {
  // TODO
}
