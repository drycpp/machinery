AC_INIT([machinery], [0.0.0], [machinery@googlegroups.com])
AC_CONFIG_SRCDIR([src/machinery.h])
AC_CONFIG_AUX_DIR([etc/aclocal])
AC_CONFIG_MACRO_DIR([etc/aclocal])
AM_INIT_AUTOMAKE([foreign -Wall -Werror dist-bzip2])
AM_SILENT_RULES([yes])
LT_INIT
AC_PROG_CC
AC_CANONICAL_HOST
AC_CHECK_HEADERS([execinfo.h])
AC_CONFIG_HEADERS([config.h])
AC_CONFIG_FILES([Makefile src/Makefile doc/Makefile doc/man/Makefile doc/manual/Makefile])
AC_OUTPUT
