#include <iostream>
#include <vector>
#include <unordered_set>
#include <queue>

using namespace std;

vector<vector<int>> adj;
vector<vector<int>> subtree;
vector<vector<int>> subsubtree;
vector<vector<int>> center;

void bfs(int start, int n, vector<int>& dist) {
    queue<int> q;
    vector<bool> visited(n + 1, false);
    q.push(start);
    visited[start] = true;
    dist[start] = 0;

    while (!q.empty()) {
        int u = q.front();
        q.pop();

        for (int v : adj[u]) {
            if (!visited[v]) {
                visited[v] = true;
                dist[v] = dist[u] + 1;
                q.push(v);
            }
        }
    }
}

bool is_connected_without(int a, int b, unordered_set<int>& excluded_edges, int n) {
    vector<int> dist_a(n + 1, -1);
    vector<int> dist_b(n + 1, -1);

    bfs(a, n, dist_a);
    bfs(b, n, dist_b);

    for (int i = 1; i <= n; ++i) {
        if (dist_a[i] != -1 && dist_b[i] != -1) {
            for (int edge : excluded_edges) {
                if (dist_a[edge] != -1 && dist_b[edge] != -1) {
                    return false;
                }
            }
        }
    }

    return true;
}

int main() {
    int n;
    cin >> n;

    adj.resize(n + 1);
    subtree.resize(n - 1, vector<int>(2));
    subsubtree.resize(n - 1, vector<vector<int>>(2, vector<int>(n)));
    center.resize(n - 1, vector<int>(2));

    for (int i = 0; i < n - 1; ++i) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    for (int i = 0; i < n - 1; ++i) {
        for (int j = 0; j < 2; ++j) {
            cin >> subtree[i][j];
        }
    }

    for (int i = 0; i < n - 1; ++i) {
        for (int j = 0; j < 2; ++j) {
            for (int k = 0; k < n; ++k) {
                cin >> subsubtree[i][j][k];
            }
        }
    }

    for (int i = 0; i < n - 1; ++i) {
        for (int j = 0; j < 2; ++j) {
            cin >> center[i][j];
        }
    }

    for (int i = 0; i < n - 1; ++i) {
        for (int j = 0; j < 2; ++j) {
            for (int k = 0; k < n; ++k) {
                if (subsubtree[i][j][k].size() > n / 2) {
                    cout << "Invalid subsubtree size" << endl;
                    return 1;
                }
            }
        }
    }

    for (int i = 0; i < n - 1; ++i) {
        for (int j = 0; j < 2; ++j) {
            if (!is_connected_without(subtree[i][j], center[i][j], {i}, n)) {
                cout << "Invalid connection" << endl;
                return 1;
            }
        }
    }

    for (int i = 0; i < n - 1; ++i) {
        for (int j = 0; j < 2; ++j) {
            cout << center[i][j] << " ";
        }
        cout << endl;
    }

    return 0;
}
