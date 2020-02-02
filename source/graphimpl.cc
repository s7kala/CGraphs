#include "graphimpl.h"
// #include "exception.h"

#include <iostream>
#include <algorithm>
#include <sstream>

// TO-DO - Change commented debug statements to ifdefs debug macros

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
    #ifdef DEBUG
    // print out adjacency list
        for(auto &it : gp.G) {
            out << it.first << ":";
            for(auto &nb : it.second) {
                out << " " << nb; 
            }
            out << '\n';
        }
    #endif
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

template <typename T>
bool exists_in(std::vector<T> list, T t) {
    return !(std::find(list.begin(), list.end(), t) == list.end());
}

int get_location(const Vertex& x, const GraphImpl& gp) {
    int location = -1, index = 0;
    for(auto &it : gp.G) {
        ++index;
        if(it.first.name == x.name) {
            location = index;
            break;
        }
    }
    return location - 1;
}

/* Build the adjacency list and initialize vertex and edge sets along
   with degree sequence from the input stream */
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
        if(!exists_in(vertex_set, vertex)) {
            int degree = 0;
            std::vector<Vertex> row;
            while(sline >> neighbour) {
                if(neighbour == vertex) std::cerr << "Loop detected, skipping this input.\n";
                else {
                    row.emplace_back(neighbour);
                    Edge e(vertex, neighbour);
                    // if edge is not already in edge set
                    if(!exists_in(edge_set, e)) {
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

/* Initialize the graph using only vertices and edges from the input stream
   Each line corresponds to either an edge or a vertex */
void input_edges(std::istream& in, GraphImpl& gp) {
    std::string line;
    while(getline(in, line)) {
        Vertex vertex_1, vertex_2;
        std::stringstream ss(line);
        ss >> vertex_1 >> vertex_2;
        // if input is an edge
        if(vertex_1.name != "" && vertex_2.name != "") {
            Edge e(vertex_1, vertex_2);
            // if edge doesn't exist
            if(!exists_in(gp.E, e)) {
                gp.E.emplace_back(e);
                bool vertex_1_exists = exists_in(gp.V, vertex_1);
                bool vertex_2_exists = exists_in(gp.V, vertex_2);
                // if both vertices don't exist
                if(!vertex_1_exists && !vertex_2_exists) {
                    gp.V.emplace_back(vertex_1);
                    gp.V.emplace_back(vertex_2);
                    std::vector<Vertex> neighbour_1, neighbour_2;
                    neighbour_1.emplace_back(vertex_2);
                    neighbour_2.emplace_back(vertex_1);
                    std::pair<Vertex, std::vector<Vertex>> p1(vertex_1, neighbour_1);
                    std::pair<Vertex, std::vector<Vertex>> p2(vertex_2, neighbour_2);
                    gp.G.emplace_back(p1);
                    gp.G.emplace_back(p2);
                } else if(vertex_1_exists && vertex_2_exists) {
                    gp.G.at(get_location(vertex_1, gp)).second.emplace_back(vertex_2);
                    gp.G.at(get_location(vertex_2, gp)).second.emplace_back(vertex_1);    
                } else if(vertex_1_exists) {
                    gp.V.emplace_back(vertex_2);
                    gp.G.at(get_location(vertex_1, gp)).second.emplace_back(vertex_2);
                    std::vector<Vertex> neighbour_2;
                    neighbour_2.emplace_back(vertex_1);
                    std::pair<Vertex, std::vector<Vertex>> p2(vertex_2, neighbour_2);
                    gp.G.emplace_back(p2);
                } else {
                    gp.V.emplace_back(vertex_1);
                    gp.G.at(get_location(vertex_2, gp)).second.emplace_back(vertex_1);
                    std::vector<Vertex> neighbour_1;
                    neighbour_1.emplace_back(vertex_2);
                    std::pair<Vertex, std::vector<Vertex>> p1(vertex_1, neighbour_1);
                    gp.G.emplace_back(p1);
                }
            }
        }
        // if input is a vertex
        if(vertex_1.name != "" && !exists_in(gp.V, vertex_1)) {
            gp.V.emplace_back(vertex_1);
            std::vector<Vertex> neighbour_1;
            std::pair<Vertex, std::vector<Vertex>> p1(vertex_1, neighbour_1);
            gp.G.emplace_back(p1);
        }
    }
    for(auto &it : gp.V) gp.vertex_degrees.insert({it, it.degree});
}

std::istream& operator>>(std::istream& in, GraphImpl& gp) {
    //input_adjacency_list(in, gp);
    // input edges/vertex
    input_edges(in, gp);
    return in;
}

// find if there is a path from x to y, assuming that both x and y exist in the graph
bool GraphImpl::path_exists(int x_location, Vertex y, std::vector<Vertex>& visited) {
    // search in neighbours of x
    for(auto &it : G.at(x_location).second) {
        // if vertex hasn't already been visited
        if(!exists_in(visited, it)) {
            if(it == y) return true;
            visited.emplace_back(it);
            if(path_exists(get_location(it, *this), y, visited)) return true;
        }
    }

    return false;
}

bool GraphImpl::is_path(Vertex x, Vertex y) {
    int x_location = get_location(x, *this);
    int y_location = get_location(y, *this);
    if(x_location != -1 && y_location != -1) {  // both vertices exist in the graph
        std::vector<Vertex> visited;
        visited.emplace_back(x);
        #ifdef DEBUG
            std::cout << "visited so far:";
            for(auto &it : visited) std::cout << ' ' << it.name;
            std::cout << "\nFinding path from " << x << " to " << y << '\n';
        #endif
        return path_exists(x_location, y, visited);
    }
    return false;
}

// if graph is connected, set connected to 1, else to 0
void GraphImpl::set_connected() {
    if(G.size() == 0) connected = 1;
    else {
      /* The graph is connected iff there is a path from each
         vertex to each other vertex in the graph */
        for(int i = 0; i < int(V.size()); ++i) {
            for(int j = i + 1; j < int(V.size()); ++j) {
                if(!is_path(V.at(i), V.at(j))) {
                    // Add ifdef debug or not?
                    std::cout << "There is no path from " << V.at(i)
                                << " to " << V.at(j) << std::endl;
                    connected = 0;
                    return;
                }
            }
        }
        connected = 1;
    }
}


// TO-DO
// if graph is bipartite, set bipartite to 1, else to 0
// assume G is non-empty
bool color_bipartite(Vertex& parent, std::vector<Vertex>& visited, GraphImpl& gp) {
    int index = get_location(parent, gp);
    // go through neigbhours of parent
    for (auto &it : gp.G.at(index).second){
        // if neigbhours haven't been visited
        if(!exists_in(visited, it)){
            visited.emplace_back(it);
            gp.G.at(get_location(it, gp)).first.color = !gp.G.at(get_location(parent, gp)).first.color;
            if(!color_bipartite(it, visited, gp)) return false;
        }
        else if(gp.G.at(get_location(parent, gp)).first.color == gp.G.at(get_location(it, gp)).first.color){
            std::cerr << "The vertices " << it << " and " << parent << " are of the same color" << std::endl;
            return false;
        }
    }
    return true;
}


void GraphImpl::set_bipartite() {
    if(G.size() == 0) bipartite = 1;
    else {
        std::vector<Vertex> visited;
        G.at(0).first.color = 0;
        visited.emplace_back(G.at(0).first);
        if(color_bipartite(G.at(0).first, visited, *this)) bipartite = 1;
        else bipartite = 0;
        // cleanup
        for(auto &it : G) {
            std::cout << it.first << ": " << it.first.color << '\n';
            it.first.color = -1;
        }
    }
}

// TO-DO
void GraphImpl::set_planar() {
    if(G.size() == 0) planar = 1;
    else {


    }
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
