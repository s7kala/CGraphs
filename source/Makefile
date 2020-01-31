CXX = g++
CXXFLAGS = -std=c++17 -Wall -MMD
EXEC = client
EXEC_G = ${EXEC}_g
OBJECTS = test_client.o graph.o graphimpl.o
DEPENDS = ${OBJECTS:.o=.d}

${EXEC}: ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} -o ${EXEC}
	${CXX} ${CXXFLAGS} -DDEBUG -g ${OBJECTS} -o ${EXEC_G}

-include ${DEPENDS}

.PHONY: clean

clean:
	rm ${OBJECTS} ${EXEC} ${EXEC_G} ${DEPENDS}
