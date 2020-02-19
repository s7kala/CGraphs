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
LIB = graph.o graphimpl.o vertex.o edge.o
LIB_G = ${LIB}
LIB_PATH = ../../source/
CLIENT_PATH = ${PWD}
OBJECTS_SPEED = speed_client.o
DEPENDS = ${OBJECTS:.o=.d}

${EXEC}: ${LIB} ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} ${LIB} -o ${EXEC}
# TO-DO
${LIB}:
	cd ${LIB_PATH} && make && mv *.o ${CLIENT_PATH} && make clean
LIB_DEBUG:
	cd ${LIB_PATH} && make debug && mv *.o ${CLIENT_PATH} && make clean

debug: CXXFLAGS += -DDEBUG -g

debug: ${EXEC_G}

speed: ${EXEC_SPEED}

${EXEC_SPEED}: ${LIB} ${OBJECTS_SPEED}
	${CXX} ${CXXFLAGS} ${OBJECTS_SPEED} ${LIB} -o ${EXEC_SPEED}

${EXEC_G}: LIB_DEBUG ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} ${LIB_G} -o ${EXEC_G}

-include ${DEPENDS}

.PHONY: clean rmlib

clean:
	-rm -f ${EXEC} ${EXEC_G} ${EXEC_SPEED} ${OBJECTS} ${OBJECTS_SPEED} *.d
rmlib:
	-rm -f ${LIB}
	
