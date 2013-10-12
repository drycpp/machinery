#!/usr/bin/env python
# This is free and unencumbered software released into the public domain.

from ctypes import CDLL, c_bool, c_char_p, c_short
from ctypes.util import find_library

try:
  libmachinery = CDLL('libmachinery.so.0')
except OSError:
  libmachinery_path = find_library('machinery')
  if libmachinery_path:
    libmachinery = CDLL(libmachinery_path)
  else:
    raise OSError('Machinery shared library not found')

VERSION_STRING = c_char_p.in_dll(libmachinery, 'machinery_version_string').value
VERSION_MAJOR  = c_short.in_dll(libmachinery, 'machinery_version_major').value
VERSION_MINOR  = c_short.in_dll(libmachinery, 'machinery_version_minor').value
VERSION_PATCH  = c_short.in_dll(libmachinery, 'machinery_version_patch').value

def version_string(): return VERSION_STRING

has_feature = libmachinery.machinery_feature_exists
has_feature.argtypes = [c_char_p]
has_feature.restype = c_bool

has_module = libmachinery.machinery_module_exists
has_module.argtypes = [c_char_p]
has_module.restype = c_bool

if __name__ == '__main__':
  print "machinery.version_string(): {}".format(version_string())
  print
  for feature_name in ('ascii', 'debug', 'unicode'):
    print "machinery.has_feature('{}'): {}".format(feature_name, has_feature(feature_name))
  print
  for module_name in ('arm', 'mips', 'x86', 'ir', 'jit'):
    print "machinery.has_module('{}'): {}".format(module_name, has_module(module_name))
  print
