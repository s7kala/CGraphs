#ifndef VERTEX_H
#define VERTEX_H

#include <iostream>

struct Vertex {
    std::string name;
    int degree;
    // add neighbours list?
    Vertex(std::string n = "", int deg = 0);
    bool operator==(const Vertex& v);
};

std::istream& operator>>(std::istream&, Vertex&);
std::ostream& operator<<(std::ostream&, const Vertex&);
bool operator<(const Vertex& v1, const Vertex& v2);

#endif