#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <limits>

using namespace std;

typedef pair<int, int> pii;

vector<int> dijkstra(int n, const vector<vector<pii>>& adj, int start) {
    vector<int> dist(n + 1, numeric_limits<int>::max());
    priority_queue<pii, vector<pii>, greater<pii>> pq;
    dist[start] = 0;
    pq.push({0, start});

    while (!pq.empty()) {
        int d = pq.top().first;
        int u = pq.top().second;
        pq.pop();

        if (d > dist[u]) continue;

        for (const auto& edge : adj[u]) {
            int v = edge.first;
            int w = edge.second;
            if (dist[u] + w < dist[v]) {
                dist[v] = dist[u] + w;
                pq.push({dist[v], v});
            }
        }
    }

    return dist;
}

int main() {
    int n;
    cin >> n;
    vector<int> u(n - 1), v(n - 1), w(n - 1);
    for (int i = 0; i < n - 1; ++i) {
        cin >> u[i] >> v[i] >> w[i];
    }

    int m;
    cin >> m;
    vector<int> army(m);
    for (int i = 0; i < m; ++i) {
        cin >> army[i];
    }

    vector<vector<pii>> adj(n + 1);
    for (int i = 0; i < n - 1; ++i) {
        adj[u[i]].push_back({v[i], w[i]});
        adj[v[i]].push_back({u[i], w[i]});
    }

    vector<int> dist_from_1 = dijkstra(n, adj, 1);
    vector<int> max_dist(n + 1, 0);

    for (int i = 2; i <= n; ++i) {
        if (adj[i].size() == 1) {
            max_dist[i] = dist_from_1[i];
        }
    }

    int max_time = 0;
    for (int i = 0; i < m; ++i) {
        vector<int> dist_from_army = dijkstra(n, adj, army[i]);
        int min_dist = numeric_limits<int>::max();
        for (int j = 2; j <= n; ++j) {
            if (adj[j].size() == 1) {
                min_dist = min(min_dist, dist_from_army[j]);
            }
        }
        max_time = max(max_time, min_dist);
    }

    cout << max_time << endl;
    return 0;
}
