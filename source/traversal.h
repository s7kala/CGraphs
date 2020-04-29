#ifndef TRAVERSAL_H
#define TRAVERSAL_H

#include "graphimpl.h"

void weighted_shortest_path(const GraphImpl&, const Vertex&, const Vertex&, std::vector<Vertex>&);
void unweighted_shortest_path(const GraphImpl&, const Vertex&, const Vertex&, std::vector<Vertex>&);

#endif