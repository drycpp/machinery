/* This is free and unencumbered software released into the public domain. */

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include "catch.hpp"

#include <machinery.h>
#include <machinery/arch/arm.h>
#include <machinery/util/buffer.h>

#include <cstdio> /* for std::sprintf() */
#include <string> /* for std::string */

using namespace machinery::arch;
using namespace machinery::arch::arm;
using namespace machinery::util;

static appendable_buffer _buffer;

static arm_emitter<decltype(_buffer)>
emit() {
  _buffer.clear();
  return arm_emitter<decltype(_buffer)>(_buffer);
}

static std::string
s(const arm_emitter<decltype(_buffer)>&) {
  static char string[4096];
  for (auto i = 0UL; i < _buffer.size(); i++) {
    std::sprintf(string + i * 2, "%02X", _buffer.data()[i]);
  }
  return std::string{string};
}

TEST_CASE("hint") {
  REQUIRE(s(emit().hint()) == "1F2003D5");
  REQUIRE(s(emit().hint(0)) == "1F2003D5");
  REQUIRE(s(emit().hint(1)) == "3F2003D5");
  REQUIRE(s(emit().hint(2)) == "5F2003D5");
  REQUIRE(s(emit().hint(3)) == "7F2003D5");
  REQUIRE(s(emit().hint(4)) == "9F2003D5");
  REQUIRE(s(emit().hint(5)) == "BF2003D5");
}

TEST_CASE("nop") {
  REQUIRE(s(emit().nop()) == "1F2003D5");
}

TEST_CASE("sev") {
  REQUIRE(s(emit().sev()) == "9F2003D5");
}

TEST_CASE("sevl") {
  REQUIRE(s(emit().sevl()) == "BF2003D5");
}

TEST_CASE("wfe") {
  REQUIRE(s(emit().wfe()) == "5F2003D5");
}

TEST_CASE("wfi") {
  REQUIRE(s(emit().wfi()) == "7F2003D5");
}

TEST_CASE("yield") {
  REQUIRE(s(emit().yield()) == "3F2003D5");
}
