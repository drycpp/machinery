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

#if defined(__arm__)
#include <machinery/arm.h>
#endif

#if defined(__mips__)
#include <machinery/mips.h>
#endif

#if defined(__ppc__) || defined(__ppc64__)
#include <machinery/ppc.h>
#endif

#if defined(__sparc__)
#include <machinery/sparc.h>
#endif

#if defined(__i386__) || defined(__x86_64__)
#include <machinery/x86.h>
#endif

#ifdef __cplusplus
}
#endif

#endif /* _MACHINERY_H */
