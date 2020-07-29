#include "../../source/graph.h"
#include "../../source/exception.h"
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
    bool test_planarity = false, test_shortest = false;
    bool test_allpaths = false;
    std::string source, dest;
    std::stringstream ss(options);
    while(ss >> flag) {
        std::string test = flag.substr(1);
        if(test == "connected") test_connected = true;
        else if(test == "bipartite") test_bipartite = true;
        else if(test == "planar") test_planarity = true;
        else if(test == "shortest"){ 
            test_shortest = true;
            std::cout << "SHORTEST PATH TEST\n";
            std::cout << "Enter source vertex:\n";
            std::cin >> source;
            std::cout << "Enter dest vertex:\n";
            std::cin >> dest;
        } else if(test == "allpaths") {
            test_allpaths = true;
            if(!test_shortest) {
                std::cout << "ALL PATH TEST\n";
                std::cout << "Enter source vertex:\n";
                std::cin >> source;
                std::cout << "Enter dest vertex:\n";
                std::cin >> dest;
            }
        }
        else std::cout << "Unknown command line option: " << flag << std::endl;
    }
    Graph g;
    std::cout << "Enter the vertices/edges in the graph(one per line)\n";
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
    if(test_shortest) {
        auto sp = g.shortest_path(source, dest);
        if(sp.empty()) std::cout << "No path found!\n";
        else {
            std::cout << "The shortest path is: ";
            for(auto it : sp)
               std::cout << it << ' ';
            std::cout << std::endl;
        }
    } if(test_allpaths) {
        auto ap = g.all_paths(source, dest);
        if(ap.empty()) std::cout << "No path found!\n";
        else {
            int i = 1;
            for(auto it : ap) {
                std::cout << "Path " << i++ << ":";
                for(auto s : it) {
                    std::cout << ' ' << s;
                }
                std::cout << '\n';
            }
        }
    }
}
