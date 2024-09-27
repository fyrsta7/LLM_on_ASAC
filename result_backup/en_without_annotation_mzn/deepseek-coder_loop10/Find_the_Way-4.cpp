#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

const int INF = 1e9;

int n, m, s, t;
vector<vector<int>> adj;
vector<pair<int, int>> roads;

int bfs() {
    vector<int> dist(n, INF);
    queue<int> q;
    q.push(s);
    dist[s] = 0;

    while (!q.empty()) {
        int u = q.front();
        q.pop();

        for (int v : adj[u]) {
            if (dist[v] == INF) {
                dist[v] = dist[u] + 1;
                q.push(v);
            }
        }
    }

    return dist[t] == INF ? -1 : dist[t];
}

int main() {
    cin >> n >> m;
    adj.resize(n);
    roads.resize(m);

    for (int i = 0; i < m; ++i) {
        int u, v;
        cin >> u >> v;
        roads[i] = {u, v};
        adj[u].push_back(v);
    }

    cin >> s >> t;

    int result = bfs();
    cout << result << endl;

    return 0;
}
