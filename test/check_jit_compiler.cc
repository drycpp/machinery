/* This is free and unencumbered software released into the public domain. */

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include "catch.hpp"

#include <machinery/jit.h>
#include <machinery/util/buffer.h>

#include <cstdio> /* for std::sprintf() */

using namespace machinery::jit;
using namespace machinery::util;

TEST_CASE("for_unknown") {
  REQUIRE_THROWS_AS(compiler_for("unknown"), std::invalid_argument);
}

#ifndef DISABLE_ARM
TEST_CASE("for_armv8_aarch64") {
  REQUIRE(compiler_for("armv8-aarch64"));
  REQUIRE(compiler_for_armv8_aarch64());
}
#endif

#ifndef DISABLE_MIPS
TEST_CASE("for_mips32") {
  REQUIRE(compiler_for("mips32"));
  REQUIRE(compiler_for_mips32());
}
#endif

#ifndef DISABLE_X86
TEST_CASE("for_x86_64") {
  REQUIRE(compiler_for("x86-64"));
  REQUIRE(compiler_for_x86_64());
}
#endif
