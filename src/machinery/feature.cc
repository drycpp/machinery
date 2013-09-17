/* This is free and unencumbered software released into the public domain. */

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include "feature.h"

static const char* const feature_names[] = {
  "ascii",
#ifdef ENABLE_DEBUG
  "debug",
#endif
#ifndef DISABLE_UNICODE
  "unicode",
#endif
};
