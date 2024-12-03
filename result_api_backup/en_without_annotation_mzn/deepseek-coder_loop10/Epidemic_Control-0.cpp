#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <limits>

using namespace std;

struct Edge {
    int to, weight;
};

vector<int> dijkstra(int n, const vector<vector<Edge>>& graph, int start) {
    vector<int> dist(n + 1, numeric_limits<int>::max());
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    dist[start] = 0;
    pq.push({0, start});

    while (!pq.empty()) {
        int d = pq.top().first;
        int u = pq.top().second;
        pq.pop();

        if (d > dist[u]) continue;

        for (const Edge& e : graph[u]) {
            int v = e.to;
            int w = e.weight;
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
    vector<vector<Edge>> graph(n + 1);
    for (int i = 1; i < n; ++i) {
        int u, v, w;
        cin >> u >> v >> w;
        graph[u].push_back({v, w});
        graph[v].push_back({u, w});
    }

    int m;
    cin >> m;
    vector<int> army(m);
    for (int i = 0; i < m; ++i) {
        cin >> army[i];
    }

    vector<int> dist_from_1 = dijkstra(n, graph, 1);
    vector<int> max_dist(n + 1, 0);

    for (int i = 2; i <= n; ++i) {
        if (graph[i].size() == 1) {
            max_dist[i] = dist_from_1[i];
        }
    }

    int max_time = 0;
    for (int i = 0; i < m; ++i) {
        vector<int> dist_from_army = dijkstra(n, graph, army[i]);
        int min_dist = numeric_limits<int>::max();
        for (int j = 2; j <= n; ++j) {
            if (graph[j].size() == 1) {
                min_dist = min(min_dist, dist_from_army[j]);
            }
        }
        max_time = max(max_time, min_dist);
    }

    cout << max_time << endl;
    return 0;
}
