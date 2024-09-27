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

    int min_len = INF;
    for (int i = 0; i < m; ++i) {
        int u = roads[i].first, v = roads[i].second;
        adj[u].erase(find(adj[u].begin(), adj[u].end(), v));
        if (!bfs()) {
            min_len = min(min_len, m - 1);
        }
        adj[u].push_back(v);
    }

    if (min_len == INF) {
        cout << m << endl;
    } else {
        cout << min_len << endl;
    }

    return 0;
}
