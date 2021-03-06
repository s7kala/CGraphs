#include "graph.h"
#include "graphimpl.h"
#include <iostream>

Graph::Graph(): pImpl{std::make_unique<GraphImpl>()} {}

Graph::~Graph() = default;

void Graph::print_properties(std::ostream &out) {
    pImpl->print_properties(out);
}

bool Graph::is_bipartite() {
    return pImpl->is_bipartite();
}

bool Graph::is_connected() {
    return pImpl->is_connected();
}

bool Graph::is_planar() {
    return pImpl->is_planar();
}

bool Graph::is_path(std::string v1, std::string v2) {
    return pImpl->is_path(Vertex(v1), Vertex(v2));
}

void Graph::add_vertex(std::string v) {
    pImpl->add_vertex(Vertex(v));
}

void Graph::delete_vertex(std::string v) {
    pImpl->delete_vertex(Vertex(v));
}

void Graph::add_edge(std::string v1, std::string v2) {
    pImpl->add_edge(Edge(Vertex(v1), Vertex(v2)));
}

void Graph::delete_edge(std::string v1, std::string v2) {
    pImpl->delete_edge(Edge(Vertex(v1), Vertex(v2)));
}


std::vector<std::string> Graph::shortest_path(std::string v1, std::string v2) {
    return pImpl->shortest_path(Vertex(v1), Vertex(v2));
}

std::vector<std::vector<std::string>> Graph::all_paths(std::string v1, std::string v2) {
    return pImpl->all_paths(Vertex(v1), Vertex(v2));
}

std::ostream &operator<<(std::ostream &out, const Graph &g) {
    out << *g.pImpl;
    return out;
}

std::istream &operator>>(std::istream &in, Graph &g) {
    in >> *g.pImpl;
    return in;
}
