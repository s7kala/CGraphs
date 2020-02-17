##############################################
#### This Makefile will build the library ####
##############################################

CXX = g++
CXXFLAGS = -std=c++17 -Wall -MMD
DEBUG_FLAGS = -DDEBUG -g
OBJECTS = graph.o graphimpl.o vertex.o edge.o
DEPENDS = ${OBJECTS:.o=.d}

all: ${OBJECTS}

debug: CXXFLAGS += ${DEBUG_FLAGS}

debug: ${OBJECTS} 

-include ${DEPENDS}

.PHONY: clean

clean:
	-rm -f *.o *.d
