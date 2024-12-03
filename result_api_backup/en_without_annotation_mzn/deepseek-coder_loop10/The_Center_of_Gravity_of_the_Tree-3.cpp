#include <iostream>
#include <vector>
#include <queue>
#include <set>

using namespace std;

vector<vector<int>> adj;
vector<vector<int>> subtree;
vector<vector<set<int>>> subsubtree;
vector<vector<int>> center;

void bfs(int start, int n, vector<bool>& visited, vector<int>& parent) {
    queue<int> q;
    q.push(start);
    visited[start] = true;
    parent[start] = -1;

    while (!q.empty()) {
        int u = q.front();
        q.pop();

        for (int v : adj[u]) {
            if (!visited[v]) {
                visited[v] = true;
                parent[v] = u;
                q.push(v);
            }
        }
    }
}

void dfs(int u, int parent, vector<int>& subtree_nodes) {
    subtree_nodes.push_back(u);
    for (int v : adj[u]) {
        if (v != parent) {
            dfs(v, u, subtree_nodes);
        }
    }
}

void solve(int n, const vector<pair<int, int>>& edges) {
    adj.resize(n + 1);
    subtree.resize(n, vector<int>(2));
    subsubtree.resize(n, vector<set<int>>(2, set<int>(n)));
    center.resize(n, vector<int>(2));

    for (const auto& edge : edges) {
        adj[edge.first].push_back(edge.second);
        adj[edge.second].push_back(edge.first);
    }

    vector<bool> visited(n + 1, false);
    vector<int> parent(n + 1);
    bfs(1, n, visited, parent);

    for (int i = 1; i < n; ++i) {
        int u = edges[i - 1].first;
        int v = edges[i - 1].second;

        vector<int> subtree_nodes_u, subtree_nodes_v;
        dfs(u, v, subtree_nodes_u);
        dfs(v, u, subtree_nodes_v);

        subtree[i - 1][0] = u;
        subtree[i - 1][1] = v;

        for (int node : subtree_nodes_u) {
            subsubtree[i - 1][0].insert(node);
        }
        for (int node : subtree_nodes_v) {
            subsubtree[i - 1][1].insert(node);
        }

        center[i - 1][0] = u;
        center[i - 1][1] = v;
    }

    for (int i = 0; i < n - 1; ++i) {
        cout << "Center[" << i + 1 << "][0] = " << center[i][0] << endl;
        cout << "Center[" << i + 1 << "][1] = " << center[i][1] << endl;
    }
}

int main() {
    int n;
    cin >> n;

    vector<pair<int, int>> edges(n - 1);
    for (int i = 0; i < n - 1; ++i) {
        cin >> edges[i].first >> edges[i].second;
    }

    solve(n, edges);

    return 0;
}
