#include <iostream>
#include <vector>

using namespace std;

const int MAXN = 300000;

vector<int> adj[MAXN + 1];
int size[MAXN + 1];
int center[MAXN + 1];
bool visited[MAXN + 1];

void dfs(int v, int parent, int n) {
    size[v] = 1;
    int max_part = 0;
    for (int u : adj[v]) {
        if (u != parent && !visited[u]) {
            dfs(u, v, n);
            size[v] += size[u];
            max_part = max(max_part, size[u]);
        }
    }
    max_part = max(max_part, n - size[v]);
    if (center[0] == -1 || max_part < center[1]) {
        center[0] = v;
        center[1] = max_part;
    }
}

void find_centers(int n) {
    center[0] = -1;
    dfs(1, -1, n);
    int root = center[0];
    center[0] = -1;
    center[1] = n;
    dfs(root, -1, n);
}

int main() {
    int T;
    cin >> T;
    while (T--) {
        int n;
        cin >> n;
        for (int i = 1; i <= n; ++i) {
            adj[i].clear();
        }
        for (int i = 0; i < n - 1; ++i) {
            int u, v;
            cin >> u >> v;
            adj[u].push_back(v);
            adj[v].push_back(u);
        }
        long long result = 0;
        for (int u = 1; u <= n; ++u) {
            for (int v : adj[u]) {
                if (u < v) { 
                    fill(visited + 1, visited + n + 1, false);
                    center[0] = -1;
                    visited[v] = true;
                    dfs(u, -1, n);
                    int center1 = center[0];
                    fill(visited + 1, visited + n + 1, false);
                    center[0] = -1;
                    visited[u] = true;
                    dfs(v, -1, n);
                    int center2 = center[0];
                    result += center1 + center2;
                }
            }
        }
        cout << result << endl;
    }
    return 0;
}