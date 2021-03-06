*************
DRY Machinery
*************

.. image:: https://api.travis-ci.org/dryproject/machinery.svg?branch=master
   :target: https://travis-ci.org/dryproject/machinery
   :alt: Travis CI build status

.. image:: https://scan.coverity.com/projects/3232/badge.svg
   :target: https://scan.coverity.com/projects/3232
   :alt: Coverity Scan build status

Toolchain machinery for compilers, code generators, assemblers, linkers, and
emulators.

Features
========

* Currently targets the x86-64, ARMv8 AArch64, and MIPS32 architectures.
* No runtime dependencies other than the system's C++ standard library.
* No build prerequisites beyond the Autotools toolchain and a C++11 compiler.
* Compatible with Clang and GCC, or any standard C++11 implementation.
* 100% free and unencumbered `public domain <http://unlicense.org/>`_ software,
  usable in any context and for any purpose.

Examples
========

x86-64 JIT calculator
---------------------

::

   #include <machinery/arch/x86.h>
   #include <machinery/util/buffer.h>
   
   #include <cstdio>  /* for std::printf() */
   #include <cstdlib> /* for std::atoi() */
   
   using namespace machinery::arch;
   using namespace machinery::arch::x86;
   using namespace machinery::util;
   
   int main(int argc, char* argv[]) {
     executable_buffer code;
     x86_emitter<executable_buffer> emit(code);
   
     /* Function prolog: */
     emit.push(reg64::rbp);
     emit.mov(reg64::rbp, reg64::rsp);
   
     /* Clear the RAX register: */
     emit.mov(reg64::rax, imm64{0});
   
     /* For each command-line argument: */
     for (auto i = 1; i < argc; i++) {
       /* Convert the argument to an integer: */
       const int arg = std::atoi(argv[i]);
   
       /* Add the integer argument to RAX: */
       emit.add(imm32(arg));
     }
   
     /* Function epilog: */
     emit.pop(reg64::rbp);
     emit.ret();
   
     /* Execute the code buffer and print out the result: */
     std::printf("%d\n", code.execute<std::int32_t>());
   
     return EXIT_SUCCESS;
   }

Build Prerequisites
===================

* Clang_ (>= 3.2) or GCC_ (>= 4.8)
* Autoconf_ (>= 2.68)
* Automake_ (>= 1.11)
* Libtool_ (>= 2.2)

.. note::

   Older releases may work, but are not actively tested for.

.. _Clang:    http://clang.llvm.org/
.. _GCC:      http://gcc.gnu.org/
.. _Autoconf: http://www.gnu.org/software/autoconf/
.. _Automake: http://www.gnu.org/software/automake/
.. _Libtool:  http://www.gnu.org/software/libtool/

Installation
============

Installation on Unix
--------------------

::

   $ ./autogen.sh
   $ ./configure                        # on Linux
   $ ./configure --with-stdlib=libc++   # on FreeBSD / Mac OS X
   $ make
   $ sudo make install
   $ sudo ldconfig                      # on Linux

Elsewhere
=========

Find this project at: GitHub_, Bitbucket_, Ohloh_, SourceForge_, `Travis
CI`_, and `Coverity Scan`_.

.. _GitHub:        http://github.com/dryproject/machinery
.. _Bitbucket:     http://bitbucket.org/dryproject/machinery
.. _Ohloh:         http://www.ohloh.net/p/machinery
.. _SourceForge:   http://sourceforge.net/projects/machinery/
.. _Travis CI:     http://travis-ci.org/dryproject/machinery
.. _Coverity Scan: http://scan.coverity.com/projects/3232

Author
======

This project is part of the `DRY <http://dryproject.org/>`_ initiative.

* `Arto Bendiken <https://github.com/bendiken>`_ - http://ar.to/

Donations
=========

If you found this software useful and would like to encourage its
maintenance and further development, please consider making a $5 donation
to the author(s) via Gratipay_ or Bitcoin_.

.. _Gratipay: https://gratipay.com/bendiken/
.. _Bitcoin:  bitcoin:15msntdJrvwesEztFdw5yf3yBbyNJSfZUb?label=machinery.dryproject.org&message=Donation

License
=======

This is free and unencumbered public domain software. For more information,
see http://unlicense.org/ or the accompanying ``UNLICENSE`` file.
