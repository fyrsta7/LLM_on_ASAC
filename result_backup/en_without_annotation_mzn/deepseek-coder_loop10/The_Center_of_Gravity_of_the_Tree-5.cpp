#include <iostream>
#include <vector>
#include <queue>
#include <unordered_set>

using namespace std;

struct Edge {
    int u, v;
};

bool bfs(int n, const vector<vector<int>>& adj, int start, int end, const unordered_set<int>& exclude) {
    vector<bool> visited(n + 1, false);
    queue<int> q;
    q.push(start);
    visited[start] = true;

    while (!q.empty()) {
        int u = q.front();
        q.pop();

        for (int v : adj[u]) {
            if (exclude.count(v)) continue;
            if (v == end) return true;
            if (!visited[v]) {
                visited[v] = true;
                q.push(v);
            }
        }
    }

    return false;
}

bool is_valid_subtree(int n, const vector<Edge>& edges, const vector<vector<int>>& adj, const vector<int>& subtree, int center) {
    for (int i = 1; i <= n; ++i) {
        if (subtree[i] == center) continue;
        for (int j = i + 1; j <= n; ++j) {
            if (subtree[j] == center) continue;
            if (!bfs(n, adj, i, j, {center})) return false;
        }
    }
    return true;
}

int main() {
    int n;
    cin >> n;

    vector<Edge> edges(n - 1);
    vector<vector<int>> adj(n + 1);

    for (int i = 0; i < n - 1; ++i) {
        cin >> edges[i].u >> edges[i].v;
        adj[edges[i].u].push_back(edges[i].v);
        adj[edges[i].v].push_back(edges[i].u);
    }

    vector<vector<int>> centers(n - 1, vector<int>(2));
    for (int i = 0; i < n - 1; ++i) {
        for (int j = 0; j < 2; ++j) {
            cin >> centers[i][j];
        }
    }

    for (int i = 0; i < n - 1; ++i) {
        for (int j = 0; j < 2; ++j) {
            int center = centers[i][j];
            vector<int> subtree(n + 1, 0);
            subtree[edges[i].u] = center;
            subtree[edges[i].v] = center;

            if (!is_valid_subtree(n, edges, adj, subtree, center)) {
                cout << "Invalid configuration" << endl;
                return 0;
            }
        }
    }

    cout << "Valid configuration" << endl;
    return 0;
}
