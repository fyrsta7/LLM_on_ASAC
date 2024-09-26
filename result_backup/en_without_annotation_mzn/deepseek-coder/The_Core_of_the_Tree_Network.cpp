#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <climits>

using namespace std;

typedef pair<int, int> pii;

vector<vector<pii>> adj;
vector<int> dist;

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
            int weight = edge.second;

            if (dist[u] + weight < dist[v]) {
                dist[v] = dist[u] + weight;
                pq.push({dist[v], v});
            }
        }
    }
}

int main() {
    int n, s;
    cin >> n >> s;

    adj.resize(n + 1);
    dist.assign(n + 1, INT_MAX);

    for (int i = 0; i < n - 1; ++i) {
        int u, v, w;
        cin >> u >> v >> w;
        adj[u].push_back({v, w});
        adj[v].push_back({u, w});
    }

    dijkstra(1);

    int max_dist = 0, farthest_node = 1;
    for (int i = 1; i <= n; ++i) {
        if (dist[i] > max_dist) {
            max_dist = dist[i];
            farthest_node = i;
        }
    }

    dist.assign(n + 1, INT_MAX);
    dijkstra(farthest_node);

    int diameter = 0;
    for (int i = 1; i <= n; ++i) {
        diameter = max(diameter, dist[i]);
    }

    vector<int> ecc(n + 1, 0);
    for (int i = 1; i <= n; ++i) {
        dist.assign(n + 1, INT_MAX);
        dijkstra(i);
        for (int j = 1; j <= n; ++j) {
            ecc[i] = max(ecc[i], dist[j]);
        }
    }

    int ans = INT_MAX;
    for (int i = 1; i <= n; ++i) {
        for (int j = i; j <= n; ++j) {
            int core_dist = 0;
            for (int k = i; k <= j; ++k) {
                core_dist += ecc[k];
            }
            if (core_dist <= s) {
                int core_ecc = 0;
                for (int k = i; k <= j; ++k) {
                    core_ecc = max(core_ecc, ecc[k]);
                }
                ans = min(ans, core_ecc);
            }
        }
    }

    cout << ans << endl;

    return 0;
}
