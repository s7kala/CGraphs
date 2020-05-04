#include "graphimpl.h"
#include "traversal.h"
// #include "exception.h"

#include <iostream>
#include <algorithm>
#include <sstream>

// ################################## METHOD ABSTRACTIONS ################################## //

// ************** OPERATOR OVERLOADS ************** //

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
        out << "Adjacency list:\n";
        for(auto const &it : gp.G) {
            out << it.first << ":";
            for(auto const &nb : it.second) {
                out << " " << nb; 
            }
            out << '\n';
        }
    #endif
    return out;
}

std::istream& operator>>(std::istream& in, GraphImpl& gp) {
    // uncomment the line below to use adjacency list for input
    // input_adjacency_list(in, gp);
    input_edges(in, gp);
    return in;
}

// ************** COMMON FUNCTIONS AND HELPERS ************** //

template <typename T>
bool exists_in(std::vector<T> list, T t) {
    return !(std::find(list.begin(), list.end(), t) == list.end());
}

// return index of a vertex in the graph
int get_location(const Vertex& x, const GraphImpl& gp) {
    int location = -1, index = 0;
    for(auto const &it : gp.G) {
        ++index;
        if(it.first.name == x.name) {
            location = index;
            break;
        }
    }
    return location - 1;
}

// TO-DO
// if graph is bipartite, set bipartite to 1, else to 0
// assume G is non-empty
bool color_bipartite(const Vertex& parent, std::map<Vertex, bool>& visited, std::map<std::string, int>& color, const GraphImpl& gp) {
    int index = get_location(parent, gp);
    // go through neigbhours of parent
    for (auto const &it : gp.G.at(index).second){
        // if neigbhours haven't been visited
        if(!visited[it]) {
            visited[it] = true;
            color[it.name] = !color[parent.name];
            if(!color_bipartite(it, visited, color, gp)) return false;
        }
        else if(color[it.name] == color[parent.name]){
            #ifdef DEBUG
                std::cout << "The vertices " << it << " and " << parent << " are of the same color" << std::endl;
            #endif
            return false;
        }
    }
    return true;
}

// **************** INPUT PROCEDURES **************** //

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
                if(neighbour == vertex) {
                    #ifdef DEBUG
                        std::cout << "Loop detected, skipping this input.\n";
                    #endif
                }
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
            std::pair<Vertex, std::vector<Vertex>> p(vertex, row);
            gp.G.emplace_back(p); 
        } 
        else {
            #ifdef DEBUG
                std::cout << "Already added this vertex! Skipping this input.\n";
            #endif
        }
    }
    gp.V = vertex_set;
    gp.E = edge_set;
}

// TO-DO optimize input
/* Initialize the graph using only vertices and edges from the input stream
   Each line corresponds to either an edge or a vertex */
void input_edges(std::istream& in, GraphImpl& gp) {
    std::string line;
    while(getline(in, line)) {
        Vertex vertex_1, vertex_2;
        double weight = 0;
        std::stringstream ss(line);
        ss >> vertex_1 >> vertex_2 >> weight;
        if(weight) gp.weighted = true;
        // if input is an edge
        if(vertex_1.name != "" && vertex_2.name != "") {
            Edge e(vertex_1, vertex_2, weight);
            // if edge doesn't exist
            if(!exists_in(gp.E, e))
                gp.add_edge(e); 
        }
        // if input is a vertex not already in the graph
        if(vertex_1.name != "" && !exists_in(gp.V, vertex_1)) {
            gp.V.emplace_back(vertex_1);
            std::vector<Vertex> neighbour_1;
            std::pair<Vertex, std::vector<Vertex>> p1(vertex_1, neighbour_1);
            gp.G.emplace_back(p1);
        }
    }
}

// ######################################## METHODS ######################################## //

void GraphImpl::print_properties(std::ostream& out) {
    out << *this;
    out << '\n';
    out << "The graph is ";
    out << (is_connected() ? "connected, " : "not connected, ");
    out << (is_bipartite() ? "bipartite." : "not bipartite.");
    out << (is_planar() ? "planar, " : "not planar, ");
    out << '\n';
}

void GraphImpl::add_vertex(const Vertex& v) {
    if(exists_in(V, v)) return;
    V.emplace_back(v);
    std::vector<Vertex> neighbours;
    std::pair<Vertex, std::vector<Vertex>> p(v, neighbours);
    G.emplace_back(p);
}

void GraphImpl::delete_vertex(const Vertex& v) {
    int loc = get_location(v, *this);
    if(loc == -1) return;
    // go through the edge set and remove associated edges
    // return E.size everytime as it may change after deletion of edge
    for(int i = 0; i < int(E.size()); ++i) {
        if(E.at(i).end1 == v || E.at(i).end2 == v)
            E.erase(E.begin() + i);
    }
    G.erase(G.begin() + loc);
    V.erase(V.begin() + loc);
}

void GraphImpl::add_edge(const Edge& e) {
    E.emplace_back(e);
    Vertex vertex_1 = e.end1, vertex_2 = e.end2;
    bool vertex_1_exists = exists_in(V, vertex_1);
    bool vertex_2_exists = exists_in(V, vertex_2);
    // if both vertices don't exist
    if(!vertex_1_exists && !vertex_2_exists) {
     // first add entries for both vertices in vertex set
        V.emplace_back(vertex_1);
        V.emplace_back(vertex_2);
        // now create vectors to store neighbours of the vertex,
        // which is the second part of each entry in the adjacency list
        std::vector<Vertex> neighbour_1, neighbour_2;
        neighbour_1.emplace_back(vertex_2);
        neighbour_2.emplace_back(vertex_1);
        // create the entries for the adjacency list
        std::pair<Vertex, std::vector<Vertex>> p1(vertex_1, neighbour_1);
        std::pair<Vertex, std::vector<Vertex>> p2(vertex_2, neighbour_2);
        G.emplace_back(p1);
        G.emplace_back(p2);
    } else if(vertex_1_exists && vertex_2_exists) { // if both vertices exist
        // find entries of both vertices and add each other in their vector
        // of neighbours
        G.at(get_location(vertex_1, *this)).second.emplace_back(vertex_2);
        G.at(get_location(vertex_2, *this)).second.emplace_back(vertex_1);    
    } else if(vertex_1_exists) {  
        V.emplace_back(vertex_2);
        G.at(get_location(vertex_1, *this)).second.emplace_back(vertex_2);
        std::vector<Vertex> neighbour_2;
        neighbour_2.emplace_back(vertex_1);
        std::pair<Vertex, std::vector<Vertex>> p2(vertex_2, neighbour_2);
        G.emplace_back(p2);
    } else {
        V.emplace_back(vertex_1);
        G.at(get_location(vertex_2, *this)).second.emplace_back(vertex_1);
        std::vector<Vertex> neighbour_1;
        neighbour_1.emplace_back(vertex_2);
        std::pair<Vertex, std::vector<Vertex>> p1(vertex_1, neighbour_1);
        G.emplace_back(p1);
    }
}

void GraphImpl::delete_edge(const Edge& e) {
    int end1_location = get_location(e.end1, *this);
    int end2_location = get_location(e.end2, *this);
    // remove from edge set
    for(int i = 0; i < int(E.size()); ++i) {
        if(E.at(i) == e) {
            E.erase(E.begin() + i);
            break;
        }
    }
    // remove from AL
    auto& end1_neighbours = G.at(end1_location).second;
    auto& end2_neighbours = G.at(end2_location).second;
    // remove end2 from end1's neighbours
    for(int i = 0; i < int(end1_neighbours.size()); ++i) {
        if(end1_neighbours.at(i) == e.end2) {
            end1_neighbours.erase(end1_neighbours.begin() + i);
            break;
        }
    }
    // remove end1 from end2's neighbours
    for(int i = 0; i < int(end2_neighbours.size()); ++i) {
        if(end2_neighbours.at(i) == e.end1) {
            end2_neighbours.erase(end2_neighbours.begin() + i);
            break;
        }
    }
}

std::vector<std::string> GraphImpl::shortest_path(const Vertex& v1, const Vertex& v2) {
    std::vector<Vertex> vertex_path;
    if(weighted) weighted_shortest_path(*this, v1, v2, vertex_path);
    else unweighted_shortest_path(*this, v1, v2, vertex_path);
    std::vector<std::string> path;
    for(auto it : vertex_path) path.emplace_back(it.name);
    return path;
}

// find if there is a path from x to y, assuming that both x and y exist in the graph
bool GraphImpl::path_exists(int x_location, const Vertex& y, std::vector<Vertex>& visited) {
    // search in neighbours of x
    for(auto const &it : G.at(x_location).second) {
        // if vertex hasn't already been visited
        if(!exists_in(visited, it)) {
            if(it == y) return true;
            visited.emplace_back(it);
            if(path_exists(get_location(it, *this), y, visited)) return true;
        }
    }

    return false;
}

bool GraphImpl::is_path(const Vertex& x, const Vertex& y) {
    int x_location = get_location(x, *this);
    int y_location = get_location(y, *this);
    if(x_location != -1 && y_location != -1) {  // both vertices exist in the graph
        std::vector<Vertex> visited;
        visited.emplace_back(x);
        #ifdef DEBUG
            std::cout << "visited so far:";
            for(auto const &it : visited) std::cout << ' ' << it.name;
            std::cout << "\nFinding path from " << x << " to " << y << '\n';
        #endif
        return path_exists(x_location, y, visited);
    }
    return false;
}

// TO-DO - improve time complexity
// if graph is connected, set connected to 1, else to 0
void GraphImpl::set_connected() {
    if(G.size() == 0) connected = 1;
    else {
      /* The graph is connected iff there is a path from each
         vertex to each other vertex in the graph */
        for(int i = 0; i < int(V.size()); ++i) {
            for(int j = i + 1; j < int(V.size()); ++j) {
                if(!is_path(V.at(i), V.at(j))) {
                    #ifdef DEBUG
                        std::cout << "There is no path from " << V.at(i)
                                  << " to " << V.at(j) << std::endl;
                    #endif
                    connected = 0;
                    return;
                }
            }
        }
        connected = 1;
    }
}

void GraphImpl::set_bipartite() {
    if(G.size() == 0) bipartite = 1;
    else {
        std::map<Vertex, bool> visited;
        std::map<std::string, int> color;
        Vertex parent = G.at(0).first;
        color[parent.name] = 0;
        visited[parent] = true;
        if(color_bipartite(G.at(0).first, visited, color, *this)) bipartite = 1;
        else bipartite = 0;
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
