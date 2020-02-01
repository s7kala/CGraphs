#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>
#include <memory>

struct GraphImpl;
class Graph {
public:
    void print_properties(std::ostream&);
    bool is_planar();
    bool is_connected();
    bool is_bipartite();
    bool is_path(std::string v1, std::string v2);
    friend std::istream& operator>>(std::istream&, Graph&);
    friend std::ostream& operator<<(std::ostream&, const Graph&);
    Graph();
    ~Graph();
private:
    std::unique_ptr<GraphImpl> pImpl;
};

#endif