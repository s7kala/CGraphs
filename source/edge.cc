#include "edge.h"

Edge::Edge(Vertex v1, Vertex v2): edge{std::make_pair(v1, v2)} {}

bool Edge::operator==(const Edge& e) {
        return ((edge.first == e.edge.first && edge.second == e.edge.second) || 
                (edge.first == e.edge.second && edge.second == e.edge.first));
    }

std::ostream& operator<<(std::ostream& out, const Edge& e) {
    out << '(' << e.edge.first << ", " << e.edge.second << ')';
    return out;
}

std::istream& operator>>(std::istream& in, Edge& e) {
    in >> e.edge.first >> e.edge.second;
    return in;
}
