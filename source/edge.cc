#include "edge.h"

Edge::Edge(Vertex v1, Vertex v2, double weight): end1{v1}, end2{v2}, weight{weight} {}

bool Edge::operator==(const Edge& e) const{
        return ((end1 == e.end1 && end2 == e.end2) || 
                (end1 == e.end2 && end2 == e.end1));
    }

std::ostream& operator<<(std::ostream& out, const Edge& e) {
    out << '(' << e.end1 << ", " << e.end2 << ')';
    return out;
}

std::istream& operator>>(std::istream& in, Edge& e) {
    in >> e.end1 >> e.end2;
    return in;
}


