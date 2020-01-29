CXX = g++
CXXFLAGS = -std=c++17 -Wall -MMD
EXEC = client
EXEC_G = ${EXEC}_g
DEBUG_EXEC = ${EXEC}_debug
OBJECTS = test_client.o graph.o graphimpl.o
DEPENDS = ${OBJECTS:.o=.d}

${EXEC}: ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} -o ${EXEC}
	${CXX} ${CXXFLAGS} -g ${OBJECTS} -o ${EXEC_G}
	${CXX} ${CXXFLAGS} -DDEBUG -g ${OBJECTS} -o ${DEBUG_EXEC}

-include ${DEPENDS}

.PHONY: clean

clean:
	rm ${OBJECTS} ${EXEC} ${EXEC_G} ${DEBUG_EXEC} ${DEPENDS}
