export LD_LIBRARY_PATH   := ../../src/machinery/.libs:$(LD_LIBRARY_PATH)
export DYLD_LIBRARY_PATH := ../../src/machinery/.libs:$(DYLD_LIBRARY_PATH)

PYTHON = python

all: check

check:
	$(PYTHON) machinery.py

.PHONY: all check
