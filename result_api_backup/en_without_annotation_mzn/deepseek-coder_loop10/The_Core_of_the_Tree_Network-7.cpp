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
        int u = pq.top().second;
        int d = pq.top().first;
        pq.pop();

        if (d > dist[u]) continue;

        for (auto& edge : adj[u]) {
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

    int farthest_node = max_element(dist.begin() + 1, dist.end()) - dist.begin();
    dist.assign(n + 1, INT_MAX);
    dijkstra(farthest_node);

    int diameter = *max_element(dist.begin() + 1, dist.end());

    vector<int> core_dist(n + 1, INT_MAX);
    for (int i = 1; i <= n; ++i) {
        if (dist[i] <= s) {
            core_dist[i] = dist[i];
        }
    }

    int ans = *max_element(core_dist.begin() + 1, core_dist.end());
    cout << ans << endl;

    return 0;
}
