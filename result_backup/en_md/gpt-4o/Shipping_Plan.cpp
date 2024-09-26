```c++
#include <iostream>
#include <vector>
#include <algorithm>
#include <limits.h>
using namespace std;

struct Edge {
    int from, to, time;
};

vector<vector<pair<int, int>>> adjList;
vector<Edge> edges;
vector<int> up, depth, maxEdge;

// For LCA with preprocessing using DFS
void dfs(int u, int parent, int dep) {
    up[u] = parent;
    depth[u] = dep;
    for (auto& [v, w] : adjList[u]) {
        if (v == parent) continue;
        maxEdge[v] = w;
        dfs(v, u, dep + 1);
    }
}

// Find the maximum edge in the path from u to v
int findMaxEdge(int u, int v) {
    if (depth[u] < depth[v]) swap(u, v);
    int max_edge = 0;
    while (depth[u] > depth[v]) {
        max_edge = max(max_edge, maxEdge[u]);
        u = up[u];
    }
    while (u != v) {
        max_edge = max(max_edge, maxEdge[u]);
        max_edge = max(max_edge, maxEdge[v]);
        u = up[u];
        v = up[v];
    }
    return max_edge;
}

int main() {
    int n, m;
    cin >> n >> m;
    adjList.resize(n + 1);
    up.resize(n + 1);
    depth.resize(n + 1);
    maxEdge.resize(n + 1, 0);
    
    for (int i = 0; i < n - 1; ++i) {
        int a, b, t;
        cin >> a >> b >> t;
        adjList[a].emplace_back(b, t);
        adjList[b].emplace_back(a, t);
        edges.push_back({a, b, t});
    }
    
    dfs(1, -1, 0);
    
    vector<pair<int, int>> plans(m);
    for (int i = 0; i < m; ++i) {
        cin >> plans[i].first >> plans[i].second;
    }

    int minTime = INT_MAX;
    for (const auto& edge : edges) {
        maxEdge[edge.from] = 0;
        maxEdge[edge.to] = 0;
        dfs(edge.from, -1, 0);
        
        int totalTime = 0;
        for (const auto& [u, v] : plans) {
            totalTime += findMaxEdge(u, v);
        }
        minTime = min(minTime, totalTime);
        
        // Restore the edge values
        maxEdge[edge.from] = edge.time;
        maxEdge[edge.to] = edge.time;
        dfs(edge.from, -1, 0);
    }
    
    cout << minTime << endl;
    return 0;
}
