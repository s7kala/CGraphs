#include "graph.h"
#include "exception.h"
#include <iostream>

// test client

int main() {
    Graph g;
    std::cout << "Enter an adjacency list for a graph. Use one line for each row:\n";
    try {
        std::cin >> g;
    } catch (Exception &e) {
        std::cout << e.what() << std::endl;
    }
    std::cout << g;
    // TO-DO
    // run client tests
    
    std::cout << (g.is_connected() ? "Connected" : "Not connected");
    std::cout << '\n';  

}