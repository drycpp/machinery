/* This is free and unencumbered software released into the public domain. */

#ifndef MACHINERY_EXTERN_H
#define MACHINERY_EXTERN_H

/**
 * @file
 *
 * C function interface for Machinery.
 */

#include "version.h"

#include <stdbool.h> /* for bool */

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Determines whether libmachinery supports a given feature.
 *
 * @param feature_name the name of the feature to check for
 * @pre `feature_name` must not be `NULL`
 * @return `true` if the feature is supported, `false` otherwise
 */
bool machinery_feature_exists(const char* feature_name);

/**
 * Determines whether libmachinery includes a given module.
 *
 * @param module_name the name of the module to check for
 * @pre `module_name` must not be `NULL`
 * @return `true` if the module is supported, `false` otherwise
 */
bool machinery_module_exists(const char* module_name);

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* MACHINERY_EXTERN_H */
