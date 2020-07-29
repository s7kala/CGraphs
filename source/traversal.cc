#include "traversal.h"
#include <queue>
#include <algorithm>

void dfs(const GraphImpl& gp, const Vertex& v1, const Vertex& v2) {

}

void bfs(const GraphImpl& gp, const Vertex& v1, const Vertex& v2) {
    
}

void weighted_shortest_path(const GraphImpl& gp, const Vertex& v1, 
        const Vertex& v2, std::vector<Vertex>& path) {

}


void unweighted_shortest_path(const GraphImpl& gp, const Vertex& source, 
        const Vertex& dest, std::vector<Vertex>& path) {
    std::map<Vertex, bool> visited;
    std::queue<Vertex> q;
    std::map<Vertex, int> distance;
    std::map<Vertex, Vertex> predecessor;

    q.push(source);
    visited[source] = true;
    distance[source] = 0;
    while(!q.empty()) {
        Vertex v = q.front();
        q.pop();
        int index = get_location(v, gp);
        for(auto u : gp.G.at(index).second) {
            if(!visited[u]) {
                visited[u] = true;
                q.push(u);
                distance[u] = distance[v] + 1;
                predecessor[u] = v;
                if(u == dest) {
                    for(Vertex i = u; distance[i] != 0; i = predecessor[i])
                        path.insert(path.begin(), i);
                    path.insert(path.begin(), source);
                    return;
                }
            }
        }
    }
}

void get_all_paths(const GraphImpl& gp, const Vertex& source, const Vertex& dest, 
        std::vector<std::vector<Vertex>>& paths) {
    std::queue<std::vector<Vertex>> q;
    std::vector<Vertex> path;
    path.emplace_back(source);
    
    q.push(path);
    while(!q.empty()) {
        path = q.front();
        q.pop();
        Vertex end = path.back();
        if(end == dest) paths.emplace_back(path);
        int index = get_location(end, gp);
        // traverse through end's neighbours
        for(auto u : gp.G.at(index).second) {
            // if u is not in the path
            if(find(path.begin(), path.end(), u) == path.end()) {
                std::vector<Vertex> newPath = path;
                newPath.emplace_back(u);
                q.push(newPath);
            }
        }
    }
}
