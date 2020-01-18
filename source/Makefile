CXX = g++
CXXFLAGS = -std=c++17 -Wall -MMD -g
EXEC = client
OBJECTS = test_client.o graph.o graphimpl.o
DEPENDS = ${OBJECTS:.o=.d}

${EXEC}: ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} -o ${EXEC}

-include ${DEPENDS}

.PHONY: clean

clean:
	rm ${OBJECTS} ${EXEC} ${DEPENDS}

