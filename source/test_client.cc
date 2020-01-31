#include "graph.h"
#include "exception.h"
#include <iostream>
#include <sstream>

// test client

int main(int argc, char* argv[]) {
    std::string options, flag;
    for(int i = 1; i < argc; ++i) {
        std::string o = argv[i];
        options += o + " ";
    }
    bool test_connected = false, test_bipartite = false;
    bool test_planarity = false;
    
    std::stringstream ss(options);
    while(ss >> flag) {
        std::string test = flag.substr(1);
        if(test == "connected") test_connected = true;
        else if(test == "bipartite") test_bipartite = true;
        else if(test == "planar") test_planarity = true;
        else std::cout << "Unknown command line option: " << flag << std::endl;
    }
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
    if(test_connected)
        std::cout << (g.is_connected() ? "Connected" : "Not connected") << std::endl;
    if(test_bipartite)
        std::cout << (g.is_bipartite() ? "Bipartite" : "Not bipartite") << std::endl;
    if(test_planarity)
        std::cout << (g.is_planar() ? "Planar" : "Not planar") << std::endl;
    
}