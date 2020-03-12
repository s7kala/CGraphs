#ifndef EDGE_H
#define EDGE_H

#include "vertex.h"
#include <iostream>

struct Edge {
    Vertex end1, end2;
    Edge(Vertex v1, Vertex v2);
    bool operator==(const Edge& e) const;
};

std::istream& operator>>(std::istream&, Edge&);
std::ostream& operator<<(std::ostream&, const Edge&);

#endif