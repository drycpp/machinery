/* This is free and unencumbered software released into the public domain. */

#ifndef _MACHINERY_H
#define _MACHINERY_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>

extern const char* const machinery_version_string;

/* ARM architecture support */
#if defined(__arm__)
#include <machinery/arm.h>
#endif

/* MIPS architecture support */
#if defined(__mips__)
#include <machinery/mips.h>
#endif

/* PowerPC architecture support */
#if defined(__ppc__) || defined(__ppc64__)
#include <machinery/ppc.h>
#endif

/* SPARC architecture support */
#if defined(__sparc__)
#include <machinery/sparc.h>
#endif

/* x86 architecture support */
#if defined(__i386__) || defined(__x86_64__)
#include <machinery/x86.h>
#endif

/* ELF format support */
#include <machinery/elf.h>

#ifdef __cplusplus
}
#endif

#endif /* _MACHINERY_H */
