CPPFLAGS = -I../../src
CXXFLAGS = -std=c++11 -stdlib=libc++ -Wall -Wextra
LDFLAGS  = -L../../src/machinery/.libs -lmachinery

PROGRAMS = jit-calc

all: $(PROGRAMS)

clean:
	$(RM) $(PROGRAMS) *.o *~

.PHONY: all clean
