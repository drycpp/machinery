export LD_LIBRARY_PATH := ../../src/machinery/.libs:$(LD_LIBRARY_PATH)

SBCL = sbcl

all: check

check:
	$(SBCL) --noinform --noprint --eval '(progn (load "check.lisp") (sb-ext:quit))'

.PHONY: all check
