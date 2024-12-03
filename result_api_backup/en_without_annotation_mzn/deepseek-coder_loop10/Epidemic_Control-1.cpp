#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <limits>

using namespace std;

typedef pair<int, int> pii;

vector<vector<pii>> adj;
vector<int> army, camp, dist;
vector<bool> is_leaf;

void dijkstra(int start) {
    priority_queue<pii, vector<pii>, greater<pii>> pq;
    dist[start] = 0;
    pq.push({0, start});

    while (!pq.empty()) {
        int d = pq.top().first;
        int u = pq.top().second;
        pq.pop();

        if (d > dist[u]) continue;

        for (auto &edge : adj[u]) {
            int v = edge.first;
            int w = edge.second;
            if (dist[u] + w < dist[v]) {
                dist[v] = dist[u] + w;
                pq.push({dist[v], v});
            }
        }
    }
}

int main() {
    int n;
    cin >> n;
    adj.resize(n + 1);
    is_leaf.assign(n + 1, true);

    for (int i = 1; i < n; ++i) {
        int u, v, w;
        cin >> u >> v >> w;
        adj[u].push_back({v, w});
        adj[v].push_back({u, w});
        is_leaf[u] = is_leaf[v] = false;
    }

    int m;
    cin >> m;
    army.resize(m);
    camp.resize(m);
    for (int i = 0; i < m; ++i) {
        cin >> army[i];
    }
    for (int i = 0; i < m; ++i) {
        cin >> camp[i];
    }

    int max_time = 0;
    for (int i = 0; i < m; ++i) {
        dist.assign(n + 1, numeric_limits<int>::max());
        dijkstra(army[i]);
        max_time = max(max_time, dist[camp[i]]);
    }

    cout << max_time << endl;

    return 0;
}
