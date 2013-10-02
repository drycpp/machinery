/* This is free and unencumbered software released into the public domain. */

#define BOOST_TEST_MODULE jit
#include <boost/test/unit_test.hpp>

#include <machinery/jit.h>
#include <machinery/util/buffer.h>

#include <cstdio> /* for std::sprintf() */

using namespace machinery::jit;
using namespace machinery::util;
