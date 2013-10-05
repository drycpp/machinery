export LD_LIBRARY_PATH   := ../../src/machinery/.libs:$(LD_LIBRARY_PATH)
export DYLD_LIBRARY_PATH := ../../src/machinery/.libs:$(DYLD_LIBRARY_PATH)

RUBY = ruby

all: check

check:
	$(RUBY) machinery.rb

.PHONY: all check
