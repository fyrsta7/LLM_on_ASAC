#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

void dfs(int u, const vector<vector<int>>& adj, vector<int>& path, vector<bool>& visited) {
    visited[u] = true;
    path.push_back(u);
    for (int v : adj[u]) {
        if (!visited[v]) {
            dfs(v, adj, path, visited);
            path.push_back(u);
        }
    }
}

int main() {
    int n, m;
    cin >> n >> m;
    vector<vector<int>> adj(n + 1);
    for (int i = 0; i < m; ++i) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    for (int i = 1; i <= n; ++i) {
        sort(adj[i].begin(), adj[i].end());
    }
    vector<int> path;
    vector<bool> visited(n + 1, false);
    dfs(1, adj, path, visited);
    for (int i = 0; i < path.size(); ++i) {
        if (i > 0) cout << " ";
        cout << path[i];
    }
    cout << endl;
    return 0;
}
