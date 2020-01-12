#include "graph.h"
#include "exception.h"
#include <iostream>

int main() {
    Graph g;
    try {
        std::cin >> g;
    } catch (Exception &e) {
        std::cout << e.what() << std::endl;
    }
    std::cout << g;
    std::cout << (g.is_connected() ? "Connected" : "Not connected");
    std::cout << '\n';  
}