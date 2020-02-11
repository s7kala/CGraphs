################################################
#### This Makefile builds the test clients #####
################################################
## TO-DO ##
CXX = g++
CXXFLAGS = -std=c++17 -Wall -MMD
EXEC = client
EXEC_G = ${EXEC}_g
EXEC_SPEED = ${EXEC}_speed
OBJECTS = test_client.o graph.o
OBJECTS_SPEED = speed_client.o graph.o graphimpl.o
DEPENDS = ${OBJECTS:.o=.d}

${EXEC}: ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} -o ${EXEC}

debug: CXXFLAGS += -DDEBUG -g

debug: ${EXEC_G}

speed: ${EXEC_SPEED}

${EXEC_SPEED}: ${OBJECTS_SPEED}
	${CXX} ${CXXFLAGS} ${OBJECTS_SPEED} -o ${EXEC_SPEED}

${EXEC_G}: ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} -o ${EXEC_G}

-include ${DEPENDS}

.PHONY: clean

clean:
	rm ${EXEC} ${EXEC_G} ${EXEC_SPEED}
