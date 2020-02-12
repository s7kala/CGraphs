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
LIB = graph.o graphimpl.o
LIB_PATH = ../../source/
OBJECTS_SPEED = speed_client.o
DEPENDS = ${OBJECTS:.o=.d}

${EXEC}: ${OBJECTS} ${LIB}
	${CXX} ${CXXFLAGS} ${OBJECTS} ${LIB} -o ${EXEC}
// TO-DO
${LIB}:

debug: CXXFLAGS += -DDEBUG -g

debug: ${EXEC_G}

speed: ${EXEC_SPEED}

${EXEC_SPEED}: ${OBJECTS_SPEED} ${LIB}
	${CXX} ${CXXFLAGS} ${OBJECTS_SPEED} ${LIB} -o ${EXEC_SPEED}

${EXEC_G}: ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} ${LIB} -o ${EXEC_G}

-include ${DEPENDS}

.PHONY: clean

clean:
	-rm -f ${EXEC} ${EXEC_G} ${EXEC_SPEED}
	
