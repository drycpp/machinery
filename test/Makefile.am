AM_CPPFLAGS += $(TEST_CPPFLAGS)
AM_CXXFLAGS += $(TEST_CXXFLAGS)
AM_LDFLAGS  += $(TEST_LDFLAGS)

LDADD = $(top_srcdir)/src/machinery/libmachinery.la

check_PROGRAMS = \
  check_util_buffer

if !DISABLE_ARM
  check_PROGRAMS += check_arch_arm
endif

if !DISABLE_X86
  check_PROGRAMS += check_arch_x86
endif

TESTS = $(check_PROGRAMS)

AM_DEFAULT_SOURCE_EXT = .cc
