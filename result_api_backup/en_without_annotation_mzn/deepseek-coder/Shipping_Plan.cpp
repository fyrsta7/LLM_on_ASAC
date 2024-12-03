#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <limits>

using namespace std;

const int INF = numeric_limits<int>::max();

struct Edge {
    int to, weight;
    Edge(int t, int w) : to(t), weight(w) {}
};

void dijkstra(int start, const vector<vector<Edge>>& graph, vector<int>& dist) {
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    dist[start] = 0;
    pq.push({0, start});

    while (!pq.empty()) {
        int u = pq.top().second;
        int d = pq.top().first;
        pq.pop();

        if (d > dist[u]) continue;

        for (const Edge& e : graph[u]) {
            int v = e.to;
            int weight = e.weight;

            if (dist[u] + weight < dist[v]) {
                dist[v] = dist[u] + weight;
                pq.push({dist[v], v});
            }
        }
    }
}

int main() {
    int n, m;
    cin >> n >> m;

    vector<vector<Edge>> graph(n + 1);
    vector<vector<Edge>> reverse_graph(n + 1);

    for (int i = 0; i < n - 1; ++i) {
        int u, v, w;
        cin >> u >> v >> w;
        graph[u].emplace_back(v, w);
        graph[v].emplace_back(u, w);
        reverse_graph[u].emplace_back(v, w);
        reverse_graph[v].emplace_back(u, w);
    }

    vector<pair<int, int>> plans(m);
    for (int i = 0; i < m; ++i) {
        cin >> plans[i].first >> plans[i].second;
    }

    int min_max_time = INF;

    for (int hole = 1; hole <= n; ++hole) {
        vector<int> dist_from_hole(n + 1, INF);
        dijkstra(hole, reverse_graph, dist_from_hole);

        int max_time = 0;
        for (const auto& plan : plans) {
            vector<int> dist_from_start(n + 1, INF);
            dijkstra(plan.first, graph, dist_from_start);

            int travel_time = dist_from_start[plan.second];
            if (dist_from_start[hole] != INF && dist_from_hole[plan.second] != INF) {
                travel_time = min(travel_time, dist_from_start[hole] + dist_from_hole[plan.second]);
            }

            max_time = max(max_time, travel_time);
        }

        min_max_time = min(min_max_time, max_time);
    }

    cout << min_max_time << endl;

    return 0;
}