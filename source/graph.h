#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>
#include <memory>

struct GraphImpl;
class Graph {
public:
    /* write basic information about graph to ostream:
        vertex set
        edge set
        degree sequence
        connectedness, bipartite, planarity 
    */
    void print_properties(std::ostream&);
    bool is_planar();
    bool is_connected();
    bool is_bipartite();
    /* Check if there is a path from vertex v1 to v2
        return false if there is no path or any input
        vertex doesn't exist 
    */
    bool is_path(std::string v1, std::string v2);
    
    friend std::istream& operator>>(std::istream&, Graph&);
    friend std::ostream& operator<<(std::ostream&, const Graph&);
    Graph();
    ~Graph();
private:
    std::unique_ptr<GraphImpl> pImpl;
};

#endif