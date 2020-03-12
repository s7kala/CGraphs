#include "vertex.h"

Vertex::Vertex(std::string n, int deg): name{n}, degree{deg} {}

bool Vertex::operator==(const Vertex& v) const { 
    return (name == v.name); 
}

bool operator<(const Vertex& v1, const Vertex& v2) { 
    return (v1.name < v2.name);
}

std::ostream& operator<<(std::ostream& out, const Vertex& v) {
    out << v.name;
    return out;
}

std::istream& operator>>(std::istream& in, Vertex& v) {
    in >> v.name;
    return in;
}
