#ifndef TRAVERSAL_H
#define TRAVERSAL_H

#include "graphimpl.h"
#include <set>

void dfs(const GraphImpl&, const Vertex&, const Vertex&);
void bfs(const GraphImpl&, const Vertex&, const Vertex&);
void weighted_shortest_path(const GraphImpl&, const Vertex&, const Vertex&, std::vector<Vertex>&);
void unweighted_shortest_path(const GraphImpl&, const Vertex&, const Vertex&, std::vector<Vertex>&);
void get_all_paths(const GraphImpl&, const Vertex&, const Vertex&, std::set<std::vector<Vertex>>&);

#endif
