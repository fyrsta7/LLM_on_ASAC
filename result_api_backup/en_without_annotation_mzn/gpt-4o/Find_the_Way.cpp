#include <iostream>
#include <vector>
#include <queue>
#include <limits.h>
using namespace std;

const int INF = INT_MAX;

int main() {
    int n, m;
    cin >> n >> m;

    vector<vector<int>> adj(n+1);
    
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
    }

    int s, t;
    cin >> s >> t;

    vector<int> dist(n+1, INF);
    vector<int> parent(n+1, -1);
    queue<int> q;

    dist[s] = 0;
    q.push(s);

    while (!q.empty()) {
        int u = q.front();
        q.pop();

        for (int v : adj[u]) {
            if (dist[v] == INF) {
                dist[v] = dist[u] + 1;
                parent[v] = u;
                q.push(v);
            }
        }
    }

    if (dist[t] == INF) {
        cout << -1 << endl;
    } else {
        cout << dist[t] << endl;
    }

    return 0;
}