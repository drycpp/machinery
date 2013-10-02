dnl configure.ac                                        -*- Autoconf -*-
dnl
dnl Process this file with `autoconf` to produce a configure script.
dnl
dnl This is free and unencumbered software released into the public domain.
AC_PREREQ([2.68])

dnl Define version information:
m4_define([VERSION_MAJOR],
  m4_esyscmd([cut -d'.' -f1 VERSION | tr -d '\n']))
m4_define([VERSION_MINOR],
  m4_esyscmd([cut -d'.' -f2 VERSION | tr -d '\n']))
m4_define([VERSION_PATCH],
  m4_esyscmd([cut -d'.' -f3 VERSION | tr -d '\n']))
m4_define([VERSION_STRING],
  m4_esyscmd([git describe --dirty --always | tr -d '\n']))

dnl Define package information:
AC_INIT([DRY Machinery], [VERSION_STRING],
  [arto@bendiken.net], [machinery],
  [https://github.com/dryproject/machinery])

dnl Configure Autoconf:
AC_CONFIG_HEADERS([src/config.h])
AC_CONFIG_SRCDIR([src/machinery.h])
AC_CONFIG_AUX_DIR([etc/aclocal])
AC_CONFIG_MACRO_DIR([etc/aclocal])

dnl Configure Automake:
AM_INIT_AUTOMAKE([foreign -Wall -Werror dist-bzip2 subdir-objects nostdinc])
AM_SILENT_RULES([yes])

dnl Check for programs:
AC_PROG_CC(clang gcc cc)
AC_PROG_CC_C99
AM_PROG_CC_C_O
AC_PROG_CPP
AC_PROG_CXX(clang++ g++ c++)
AC_PROG_CXXCPP
AC_USE_SYSTEM_EXTENSIONS
m4_ifdef([AM_PROG_AR], [AM_PROG_AR])
LT_INIT
AC_LANG([C++])
AX_CXX_COMPILE_STDCXX_11([noext])

dnl Check for configuration options:
# --with-stdlib=libstdc++|libc++
AC_ARG_WITH([stdlib],
  [AS_HELP_STRING([--with-stdlib=LIB], [specify the C++ standard library to use [default=system]])],
  [], [with_stdlib=system])
AS_IF([test "x$with_stdlib" != "xsystem"],
  [CXXFLAGS="$CXXFLAGS -stdlib=$with_stdlib"
   LDFLAGS="$LDFLAGS -stdlib=$with_stdlib"])
# --enable-debug/--disable-debug
AC_ARG_ENABLE([debug],
  [AS_HELP_STRING([--enable-debug], [build with debugging support [default=no]])],
  [], [enable_debug=no])
AS_IF([test "x$enable_debug" != "xno"],
  [AC_DEFINE([DEBUG], [1], [Enable debugging support.])],
  [AC_DEFINE([NDEBUG], [1], [Disable assertions.])])
AM_CONDITIONAL([ENABLE_DEBUG], [test "x$enable_debug" != "xno"])
# --enable-unicode/--disable-unicode
AC_ARG_ENABLE([unicode],
  [AS_HELP_STRING([--disable-unicode], [omit support for Unicode strings])])
AS_IF([test "x$enable_unicode" == "xno"],
  [AC_DEFINE([DISABLE_UNICODE], 1, [Define to disable Unicode string support.])])
# --enable-*/--disable-*
AC_DEFUN([AX_ARG_DISABLE_MODULE], [dnl
  m4_define([MODULE_ID], m4_translit([$1], [-a-z], [_A-Z]))
  AC_ARG_ENABLE([$1],
    [AS_HELP_STRING([--enable-$1], [include support for $2])], [], [enable_$1=no])
  AS_IF([test "x$enable_$1" == "xno"],
    [AC_DEFINE([DISABLE_]MODULE_ID, 1, [Define to disable $2.])])
  AM_CONDITIONAL([DISABLE_]MODULE_ID, [test "x$enable_$1" == "xno"])
])
AC_DEFUN([AX_ARG_ENABLE_MODULE], [dnl
  m4_define([MODULE_ID], m4_translit([$1], [-a-z], [_A-Z]))
  AC_ARG_ENABLE([$1],
    [AS_HELP_STRING([--disable-$1], [omit support for $2])], [], [enable_$1=yes])
  AS_IF([test "x$enable_$1" == "xno"],
    [AC_DEFINE([DISABLE_]MODULE_ID, 1, [Define to disable $2.])])
  AM_CONDITIONAL([DISABLE_]MODULE_ID, [test "x$enable_$1" == "xno"])
])
AX_ARG_DISABLE_MODULE([arm], [the ARMv8 AArch64 architecture]) # --enable-arm/--disable-arm
AX_ARG_ENABLE_MODULE([x86], [the x86/x86-64 architectures])    # --enable-x86/--disable-x86
AX_ARG_ENABLE_MODULE([ir],  [the target-independent IR])       # --enable-ir/--disable-ir
AX_ARG_ENABLE_MODULE([jit], [the target-independent JIT])      # --enable-jit/--disable-jit

dnl Check for libraries:
AX_BOOST_BASE([1.48], [AX_BOOST_UNIT_TEST_FRAMEWORK])

dnl Check for header files:
AC_LANG_PUSH([C])
AC_HEADER_ASSERT
AC_HEADER_STDBOOL
AC_LANG_POP([C])

dnl Check for types:

dnl Check for structures:

dnl Check for compiler characteristics:
AC_CANONICAL_HOST
AM_CPPFLAGS="$AM_CPPFLAGS -I\$(top_srcdir)/src -iquote \$(srcdir)"
AM_CXXFLAGS="$AM_CXXFLAGS -Wall -Wextra -pipe"
AM_LDFLAGS="$AM_LDFLAGS"
TEST_CPPFLAGS="$AM_CPPFLAGS \$(BOOST_CPPFLAGS) -DBOOST_TEST_DYN_LINK"
TEST_CXXFLAGS="$AM_CXXFLAGS"
TEST_LDFLAGS="$AM_LDFLAGS \$(BOOST_LDFLAGS) \$(BOOST_UNIT_TEST_FRAMEWORK_LIB)"
AC_SUBST([AM_CPPFLAGS])
AC_SUBST([AM_CXXFLAGS])
AC_SUBST([AM_LDFLAGS])
AC_SUBST([TEST_CPPFLAGS])
AC_SUBST([TEST_CXXFLAGS])
AC_SUBST([TEST_LDFLAGS])

dnl Check for library functions:

dnl Check for system services:

dnl Generate output:
AC_CONFIG_FILES([Makefile src/Makefile src/machinery/Makefile test/Makefile])
AC_SUBST([PACKAGE_VERSION_MAJOR], ["VERSION_MAJOR"])
AC_SUBST([PACKAGE_VERSION_MINOR], ["VERSION_MINOR"])
AC_SUBST([PACKAGE_VERSION_PATCH], ["VERSION_PATCH"])
AC_CONFIG_FILES([src/machinery/version.h])
AC_OUTPUT
