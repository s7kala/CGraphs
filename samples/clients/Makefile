################################################
#### This Makefile builds the test clients #####
################################################
## TO-DO ##
CXX = g++
CXXFLAGS = -std=c++17 -Wall -MMD
EXEC = client
EXEC_G = ${EXEC}_g
EXEC_SPEED = ${EXEC}_speed
OBJECTS = test_client.o
LIB = graph.o graphimpl.o vertex.o edge.o planar.o traversal.o
LIB_G = ${LIB}
LIB_PATH = ../../source/
CLIENT_PATH = $(shell pwd)
OBJECTS_SPEED = speed_client.o
DEPENDS = ${OBJECTS:.o=.d}

${EXEC}: ${LIB} ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} ${LIB} -o ${EXEC}
# TO-DO
${LIB}:
	echo ${CLIENT_PATH}
	cd ${LIB_PATH} && make && mv ${LIB} ${CLIENT_PATH} && make clean
LIB_DEBUG:
	cd ${LIB_PATH} && make debug && mv ${LIB} ${CLIENT_PATH} && make clean

debug: CXXFLAGS += -DDEBUG -g

debug: ${EXEC_G}

speed: ${EXEC_SPEED}

${EXEC_SPEED}: ${LIB} ${OBJECTS_SPEED}
	${CXX} ${CXXFLAGS} ${OBJECTS_SPEED} ${LIB} -o ${EXEC_SPEED}

${EXEC_G}: LIB_DEBUG ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} ${LIB_G} -o ${EXEC_G}

-include ${DEPENDS}

.PHONY: clean clean_all

clean:
	-rm -f ${EXEC} ${EXEC_G} ${EXEC_SPEED} ${OBJECTS} ${OBJECTS_SPEED} *.d
clean_all:
	-rm -f *.o *d ${EXEC} ${EXEC_G}
	
