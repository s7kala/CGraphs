#ifndef GRAPHIMPL_H
#define GRAPHIMPL_H

#include "graph.h"

#include <vector>
#include <string>
#include <map>
#include <utility>

struct Vertex {
    std::string name;
    int degree;
    Vertex(std::string n = "", int deg = 0): name{n}, degree{deg} {}
    bool operator==(const Vertex &v) { return (name == v.name); }
};

struct Edge {
    std::pair<Vertex, Vertex> edge;
    Edge(Vertex v1, Vertex v2): 
        edge{std::make_pair(v1, v2)} {}
    bool operator==(const Edge& e) {
        return ((edge.first == e.edge.first && edge.second == e.edge.second) || 
                (edge.first == e.edge.second && edge.second == e.edge.first));
    }
};


struct GraphImpl {
    // fields
    // adjacency list
    std::vector<std::pair<Vertex, std::vector<Vertex>>> G;
    std::vector<Vertex> V;              // vertex set
    std::vector<Edge> E;                // edge set
    std::map<Vertex, int> vertex_degrees;
    int vertices = 0, edges = 0;
    bool planar, bipartite, has_perfect_matching, connected;
    std::vector<Vertex> min_cover;
    std::vector<Edge> max_matching;

    // methods
    bool is_bipartite();
    bool is_planar();
    bool is_connected();
    bool is_path(Vertex v1, Vertex v2);
private:
    bool path_exists(int x_location, Vertex y, std::vector<Vertex>& visited);
    int get_location(Vertex x);

};

std::istream& operator>>(std::istream&, GraphImpl&);
std::istream& operator>>(std::istream&, Vertex&);
std::istream& operator>>(std::istream&, Edge&);
std::ostream& operator<<(std::ostream&, const GraphImpl&);
std::ostream& operator<<(std::ostream&, const Vertex&);
std::ostream& operator<<(std::ostream&, const Edge&);

#endif