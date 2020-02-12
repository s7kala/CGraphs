##############################################
#### This Makefile will build the library ####
##############################################

CXX = g++
CXXFLAGS = -std=c++17 -Wall -MMD
OBJECTS = graph.o graphimpl.o
DEPENDS = ${OBJECTS:.o=.d}

all: ${OBJECTS}

-include ${DEPENDS}

.PHONY: clean

clean:
	-rm -f *.o *.d
