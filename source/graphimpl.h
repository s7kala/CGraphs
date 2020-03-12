#ifndef GRAPHIMPL_H
#define GRAPHIMPL_H

#include "vertex.h"
#include "edge.h"

#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <utility>

struct GraphImpl {
    // fields
    // adjacency list
    std::vector<std::pair<Vertex, std::vector<Vertex>>> G;
    std::vector<Vertex> V;              // vertex set
    std::vector<Edge> E;                // edge set
    std::vector<Vertex> min_cover;
    std::vector<Edge> max_matching;
    // -1 for not set, 0 for false, 1 for true
    int planar = -1, bipartite = -1, connected = -1, has_perfect_matching = -1;
    // methods
    bool is_bipartite();
    bool is_planar();
    bool is_connected();
    bool is_path(const Vertex& v1, const Vertex& v2);
    void print_properties(std::ostream&);
    void add_vertex(const Vertex& v);
    void delete_vertex(const Vertex& v);
    void add_edge(const Edge& e);
    void delete_edge(const Edge& e);
    std::vector<std::string> shortest_path(const Vertex& v1, const Vertex& v2);
private:
    bool path_exists(int x_location, const Vertex& y, std::vector<Vertex>& visited);
    void set_planar();
    void set_bipartite();
    void set_connected();
    void set_has_perfect_matching();
};


// Operator Overloads
std::istream& operator>>(std::istream&, GraphImpl&);
std::ostream& operator<<(std::ostream&, const GraphImpl&);


// Method Abstractions
template <typename T>
bool exists_in(std::vector<T> list, T t);
int get_location(const Vertex& x, const GraphImpl& gp);
bool color_bipartite(Vertex& parent, std::vector<Vertex>& visited, std::map<std::string, int>& color, GraphImpl& gp);
void input_adjacency_list(std::istream& in, GraphImpl& gp);
void input_edges(std::istream& in, GraphImpl& gp);


#endif