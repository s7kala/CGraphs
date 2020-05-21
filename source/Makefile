##############################################
#### This Makefile will build the library ####
##############################################

CXX = g++
CXXFLAGS = -std=c++17 -Wall -MMD -O2
DEBUG_FLAGS = -DDEBUG -g
OBJECTS = graph.o graphimpl.o vertex.o edge.o planar.o traversal.o
DEPENDS = ${OBJECTS:.o=.d}

all: ${OBJECTS}

debug: CXXFLAGS += ${DEBUG_FLAGS}

debug: ${OBJECTS}

release: ${OBJECTS} 

-include ${DEPENDS}

.PHONY: clean

clean:
	-rm -f *.o *.d
