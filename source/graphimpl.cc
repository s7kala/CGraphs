#include "graphimpl.h"
// #include "exception.h"

#include <iostream>
#include <algorithm>
#include <sstream>

bool operator<(const Vertex& v1, const Vertex& v2) { 
    return (v1.degree < v2.degree);
}

std::ostream& operator<<(std::ostream& out, const Vertex& v) {
    out << v.name;
    return out;
}

std::ostream& operator<<(std::ostream& out, const Edge& e) {
    out << '(' << e.edge.first << ", " << e.edge.second << ')';
    return out;
}

std::istream& operator>>(std::istream& in, Vertex& v) {
    in >> v.name;
    return in;
}

std::istream& operator>>(std::istream& in, Edge& e) {
    in >> e.edge.first >> e.edge.second;
    return in;
}

std::ostream& operator<<(std::ostream& out, const GraphImpl& gp) {
    out << "V(G) = {";
    for(int i = 0; i < int(gp.V.size()); ++i) {
        out << gp.V.at(i);
        if(i < int(gp.V.size() - 1)) out << ", ";
    }
    out << "}\n";
    out << "E(G) = {";
    for(int i = 0; i < int(gp.E.size()); ++i) {
        out << gp.E.at(i);
        if(i < int(gp.E.size() - 1)) out << ", ";
    }
    out << "}\n";
    return out;
}

void GraphImpl::print_properties(std::ostream& out) {
    out << *this;
    out << "Degree sequence: ";
    for(auto &it : vertex_degrees)
        out << it.second << ' ';
    out << '\n';
    out << "The graph is ";
    out << (is_planar() ? "planar, " : "not planar, ");
    out << (is_connected() ? "connected, " : "not connected, ");
    out << (is_bipartite() ? "bipartite." : "not bipartite.");
    out << '\n';
}

void input_adjacency_list(std::istream& in, GraphImpl& gp) {
    // initialize vertex set, edge set and degree set as well
    Vertex vertex, neighbour;
    std::vector<Vertex> vertex_set;
    std::vector<Edge> edge_set;
    std::string line;
    while(getline(in, line)) {
        std::stringstream sline(line);
        sline >> vertex;
        // if element is not already in vertex set
        if(std::find(vertex_set.begin(), vertex_set.end(), vertex) == vertex_set.end()) {
            int degree = 0;
            std::vector<Vertex> row;
            while(sline >> neighbour) {
                if(neighbour == vertex) std::cerr << "Loop detected, skipping this input.\n";
                else {
                    row.emplace_back(neighbour);
                    Edge e(vertex, neighbour);
                    // if edge is not already in edge set
                    if(std::find(edge_set.begin(), edge_set.end(), e) == edge_set.end()) {
                        edge_set.emplace_back(e);
                    }
                    degree++;
                }
            }
            vertex.degree = degree;
            vertex_set.emplace_back(vertex);
            gp.vertex_degrees.insert({vertex, degree});
            std::pair<Vertex, std::vector<Vertex>> p(vertex, row);
            gp.G.emplace_back(p); 
        } else std::cerr << "Already added this vertex! Skipping this input.\n";
    }
    gp.V = vertex_set;
    gp.E = edge_set;
}

std::istream& operator>>(std::istream& in, GraphImpl& gp) {
    input_adjacency_list(in, gp);
    return in;
}

int GraphImpl::get_location(Vertex x) {
    int location = -1, index = 0;
    for(auto &it : G) {
        ++index;
        if(it.first == x) {
            location = index;
            break;
        }
    }
    return location - 1;
}

// TO-DO
bool GraphImpl::path_exists(int x_location, Vertex y, std::vector<Vertex>& visited) {
    /*
  //  if(x_location == -1) return false;
    for(auto &it : G.at(x_location).second) {
        // if vertex hasn't already been visited
        if(std::find(visited.begin(), visited.end(), it) == visited.end()) {
            if(it == y) return true;
            visited.emplace_back(it);
            bool b = path_exists(get_location(it), y, visited);
        }
    }
    */
    return false;
}

// TO-DO
bool GraphImpl::is_path(Vertex x, Vertex y) {
    int x_location = get_location(x);
    int y_location = get_location(y);
    if(x_location != -1 && y_location != -1) {  // both vertices exist in the graph
        std::vector<Vertex> visited;
        visited.emplace_back(x);
        std::cout << "Finding path from " << x << " to " << y << '\n';
        return path_exists(x_location, y, visited);
    }
    return false;
}

// TO-DO
void GraphImpl::set_connected() {
    int vsize = V.size();
    for(int i = 0; i < vsize; ++i) {
        for(int j = i + 1; j < vsize; ++j) {
            if(!is_path(V.at(i), V.at(j))) {
                std::cout << "There is no path from " << V.at(i)
                          << " to " << V.at(j) << std::endl;
                connected = 0;
                return;
            }
        }
    }
    connected = 1;
}

// TO-DO
void GraphImpl::set_bipartite() {

}

// TO-DO
void GraphImpl::set_planar() {

}

bool GraphImpl::is_connected() {
    // if connected is not set then set connected
    if(connected < 0) set_connected();
    return (connected == 1);
}

bool GraphImpl::is_bipartite() {
    // if bipartite is not set then set bipartite
    if(bipartite < 0) set_bipartite();
    return (bipartite == 1);
}

bool GraphImpl::is_planar() {
    // if planar is not set then set planar
    if(planar < 0) set_planar();
    return (planar == 1);
}
