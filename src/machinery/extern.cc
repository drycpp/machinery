/* This is free and unencumbered software released into the public domain. */

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include "extern.h"

#include <cassert> /* for assert() */

bool
machinery_module_exists(const char* const module_name) {
  assert(module_name != nullptr);

  if (module_name != nullptr) {
    // TODO
  }

  return false; /* not found */
}

bool
machinery_feature_exists(const char* const feature_name) {
  assert(feature_name != nullptr);

  if (feature_name != nullptr) {
    // TODO
  }

  return false; /* not found */
}
