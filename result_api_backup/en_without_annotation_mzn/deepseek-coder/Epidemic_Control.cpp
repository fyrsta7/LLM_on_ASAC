#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <limits>

using namespace std;

struct Edge {
    int to, weight;
};

vector<int> dijkstra(const vector<vector<Edge>>& graph, int start) {
    int n = graph.size();
    vector<int> dist(n, numeric_limits<int>::max());
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

    vector<int> dist_from_1 = dijkstra(graph, 1);
    vector<int> max_time(n + 1, 0);

    for (int i = 0; i < m; ++i) {
        vector<int> dist_from_army = dijkstra(graph, army[i]);
        for (int j = 1; j <= n; ++j) {
            max_time[j] = max(max_time[j], dist_from_army[j]);
        }
    }

    int result = *max_element(max_time.begin(), max_time.end());
    cout << result << endl;

    return 0;
}
