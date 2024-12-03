#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <limits>

using namespace std;

const int INF = numeric_limits<int>::max();

vector<vector<pair<int, int>>> graph;

vector<int> dijkstra(int start, int n) {
    vector<int> dist(n, INF);
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    dist[start] = 0;
    pq.push({0, start});

    while (!pq.empty()) {
        int d = pq.top().first;
        int u = pq.top().second;
        pq.pop();

        if (d > dist[u]) continue;

        for (auto &edge : graph[u]) {
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
    int n, s;
    cin >> n >> s;

    graph.resize(n);
    for (int i = 0; i < n - 1; ++i) {
        int u, v, w;
        cin >> u >> v >> w;
        graph[u - 1].push_back({v - 1, w});
        graph[v - 1].push_back({u - 1, w});
    }

    vector<int> dist_from_1 = dijkstra(0, n);
    int farthest_node = max_element(dist_from_1.begin(), dist_from_1.end()) - dist_from_1.begin();
    vector<int> dist_from_farthest = dijkstra(farthest_node, n);
    int diameter = *max_element(dist_from_farthest.begin(), dist_from_farthest.end());

    int ans = INF;
    for (int i = 0; i < n; ++i) {
        for (int j = i; j < n; ++j) {
            if (dist_from_farthest[i] + dist_from_farthest[j] <= s) {
                vector<int> core_dist = dijkstra(i, n);
                int ecc = 0;
                for (int k = 0; k < n; ++k) {
                    ecc = max(ecc, core_dist[k]);
                }
                ans = min(ans, ecc);
            }
        }
    }

    cout << ans << endl;
    return 0;
}
