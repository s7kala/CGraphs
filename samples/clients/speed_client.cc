#include "../..//source/graph.h"
#include "../../source/exception.h"
#include <iostream>
#include <sstream>
#include <chrono>
#include <fstream>

// speed test client

// test types
bool test_connected = false, test_bipartite = true;
bool test_planarity = false;

void run_tests(Graph& g);

int main(int argc, char* argv[]) {
    
    // take input from file(s)
    if(argc > 1) {
        std::string tests, test;
        for(int i = 1; i < argc; ++i) {
            std::string o = argv[i];
            tests += o + " ";
        }

        std::stringstream ss(tests);
        while(ss >> test) {
            Graph g;
            std::ifstream file(test);
            file >> g;
            std::cout << "---------------------------------\n";
            std::cout << g;
            run_tests(g);
        }
    }
    // take input from stdin
    else {
        Graph g;
        std::cout << "Enter the vertices/edges in the graph(one per line)\n";
        try {
            std::cin >> g;
        } catch (Exception &e) {
            std::cout << e.what() << std::endl;
        }
        std::cout << g;
    }
}

void run_tests(Graph& g) {
    // run client tests
    double time_elapsed;
    if(test_connected) {
        clock_t start_connected = clock();
        std::cout << (g.is_connected() ? "Connected" : "Not connected") << std::endl;
        clock_t end_connected = clock();
        time_elapsed = (double)(end_connected - start_connected) / CLOCKS_PER_SEC;
        std::cout << "Time elapsed for connected is " << time_elapsed << " seconds\n";
    }
    if(test_bipartite) {
        clock_t start_bipartite = clock();
        std::cout << (g.is_bipartite() ? "Bipartite" : "Not bipartite") << std::endl;
        clock_t end_bipartite = clock();
        time_elapsed = (double)(end_bipartite - start_bipartite) / CLOCKS_PER_SEC;
        std::cout << "Time elapsed for bipartite is " << time_elapsed << " seconds\n";
    }
    if(test_planarity) {
        clock_t start_planar = clock();
        std::cout << (g.is_planar() ? "Planar" : "Not planar") << std::endl;
        clock_t end_planar = clock();
        time_elapsed = (double)(end_planar - start_planar) / CLOCKS_PER_SEC;
        std::cout << "Time elapsed for planar is " << time_elapsed << " seconds\n";
    }
    
}