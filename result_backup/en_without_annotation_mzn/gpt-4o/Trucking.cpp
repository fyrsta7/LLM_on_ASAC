#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>

using namespace std;

struct Edge {
    int u, v, weight;
};

vector<vector<int>> graph;
vector<vector<int>> weights;
vector<Edge> edges;
vector<int> queries;

// Function to perform DFS and find the minimum weight in the path
bool dfs(int u, int dest, vector<bool> &visited, int &min_weight) {
    if (u == dest) return true;
    visited[u] = true;
    for (int v = 0; v < graph[u].size(); v++) {
        if (!visited[graph[u][v]]) {
            min_weight = min(min_weight, weights[u][graph[u][v]]);
            if (dfs(graph[u][v], dest, visited, min_weight)) return true;
            min_weight = min(min_weight, weights[graph[u][v]][u]);
        }
    }
    return false;
}

int main() {
    int n, m;
    cin >> n >> m;

    graph.resize(n + 1);
    weights.resize(n + 1, vector<int>(n + 1, INT_MAX));

    for (int i = 0; i < m; i++) {
        int u, v, weight;
        cin >> u >> v >> weight;
        graph[u].push_back(v);
        graph[v].push_back(u);
        weights[u][v] = weight;
        weights[v][u] = weight;
    }

    int q;
    cin >> q;
    vector<int> start(q), end(q);

    for (int i = 0; i < q; i++) {
        cin >> start[i] >> end[i];
    }

    for (int i = 0; i < q; i++) {
        vector<bool> visited(n + 1, false);
        int min_weight = INT_MAX;
        if (dfs(start[i], end[i], visited, min_weight)) {
            cout << min_weight << "\n";
        } else {
            cout << "-1\n";
        }
    }

    return 0;
}