#!/usr/bin/env ruby
# This is free and unencumbered software released into the public domain.

require 'ffi' # @see https://rubygems.org/gems/ffi

##
# Ruby FFI for the `libmachinery` native library.
#
# @see http://machinery.dryproject.org/
module Machinery extend FFI::Library
  ffi_lib ['machinery', 'libmachinery.so.0']

  attach_variable :machinery_version_string, :string
  attach_function :machinery_feature_exists, [:string], :bool
  attach_function :machinery_module_exists, [:string], :bool

  ##
  # Returns the library version string.
  #
  # @return [String] a version string in "x.y.z" form
  def self.version_string
    machinery_version_string
  end

  ##
  # Determines whether the library supports a given feature.
  #
  # @param  [#to_s] feature_name the name of the feature, e.g. `:ascii`
  # @return [Boolean] `true` if the feature is supported, `false` otherwise
  def self.has_feature?(feature_name)
    machinery_feature_exists(feature_name.to_s)
  end

  ##
  # Determines whether the library includes a given module.
  #
  # @param  [#to_s] module_name the name of the module, e.g. `:x86`
  # @return [Boolean] `true` if the module is supported, `false` otherwise
  def self.has_module?(module_name)
    machinery_module_exists(module_name.to_s)
  end
end

if __FILE__ == $0
  puts "Machinery.version_string: %s" % Machinery.version_string
  puts
  %w(ascii debug unicode).each do |feature_name|
    puts "Machinery.has_feature?(:#{feature_name}): %s" % Machinery.has_feature?(feature_name)
  end
  puts
  %w(arm mips x86 ir jit).each do |module_name|
    puts "Machinery.has_module?(:#{module_name}) %s" % Machinery.has_module?(module_name)
  end
  puts
end
