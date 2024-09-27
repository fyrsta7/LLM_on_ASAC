#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <climits>

using namespace std;

typedef pair<int, int> pii;

vector<int> dijkstra(int n, int m, const vector<vector<pii>>& adj, int start, int hole) {
    vector<int> dist(n, INT_MAX);
    priority_queue<pii, vector<pii>, greater<pii>> pq;
    dist[start] = 0;
    pq.push({0, start});

    while (!pq.empty()) {
        int u = pq.top().second;
        int d = pq.top().first;
        pq.pop();

        if (d > dist[u]) continue;

        for (auto& edge : adj[u]) {
            int v = edge.first;
            int w = edge.second;
            if (w == 0 && u != hole && v != hole) continue;
            if (dist[u] + w < dist[v]) {
                dist[v] = dist[u] + w;
                pq.push({dist[v], v});
            }
        }
    }

    return dist;
}

int main() {
    int n, m;
    cin >> n >> m;

    vector<vector<pii>> adj(n);
    for (int i = 0; i < n - 1; ++i) {
        int u, v, w;
        cin >> u >> v >> w;
        adj[u - 1].push_back({v - 1, w});
        adj[v - 1].push_back({u - 1, w});
    }

    vector<pii> plans(m);
    for (int i = 0; i < m; ++i) {
        cin >> plans[i].first >> plans[i].second;
        plans[i].first--;
        plans[i].second--;
    }

    int min_max_time = INT_MAX;
    for (int hole = 0; hole < n; ++hole) {
        int max_time = 0;
        for (auto& plan : plans) {
            vector<int> dist = dijkstra(n, m, adj, plan.first, hole);
            max_time = max(max_time, dist[plan.second]);
        }
        min_max_time = min(min_max_time, max_time);
    }

    cout << min_max_time << endl;

    return 0;
}
