#ifndef TRAVERSAL_H
#define TRAVERSAL_H

#include "graphimpl.h"

void dfs(const GraphImpl&, const Vertex&, const Vertex&);
void bfs(const GraphImpl&, const Vertex&, const Vertex&);
void weighted_shortest_path(const GraphImpl&, const Vertex&, const Vertex&, std::vector<Vertex>&);
void unweighted_shortest_path(const GraphImpl&, const Vertex&, const Vertex&, std::vector<Vertex>&);

#endif