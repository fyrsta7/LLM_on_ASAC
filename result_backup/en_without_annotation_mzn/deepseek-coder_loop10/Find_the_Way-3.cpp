#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

const int INF = 1e9;

int n, m, s, t;
vector<vector<int>> adj;
vector<pair<int, int>> roads;

bool bfs() {
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
    return dist[t] != INF;
}

int main() {
    cin >> n >> m;
    adj.resize(n);
    roads.resize(m);
    for (int i = 0; i < m; ++i) {
        int u, v;
        cin >> u >> v;
        --u; --v;
        roads[i] = {u, v};
        adj[u].push_back(v);
    }
    cin >> s >> t;
    --s; --t;

    if (!bfs()) {
        cout << "-1" << endl;
        return 0;
    }

    vector<int> dist(n, INF);
    vector<int> parent(n, -1);
    queue<int> q;
    q.push(s);
    dist[s] = 0;
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

    vector<int> path;
    for (int v = t; v != -1; v = parent[v]) {
        path.push_back(v);
    }
    reverse(path.begin(), path.end());

    int len = path.size() - 1;
    cout << len << endl;

    return 0;
}
