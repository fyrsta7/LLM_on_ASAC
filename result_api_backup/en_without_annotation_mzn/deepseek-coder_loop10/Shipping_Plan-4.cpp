#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <limits>

using namespace std;

const int INF = numeric_limits<int>::max();

struct Edge {
    int to, cost;
};

vector<int> dijkstra(int start, const vector<vector<Edge>>& graph, int hole) {
    int n = graph.size();
    vector<int> dist(n, INF);
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    dist[start] = 0;
    pq.push({0, start});

    while (!pq.empty()) {
        int cost = pq.top().first;
        int u = pq.top().second;
        pq.pop();

        if (cost > dist[u]) continue;

        for (const Edge& e : graph[u]) {
            if (e.to == hole) continue;
            int new_cost = cost + e.cost;
            if (new_cost < dist[e.to]) {
                dist[e.to] = new_cost;
                pq.push({new_cost, e.to});
            }
        }
    }

    return dist;
}

int main() {
    int n, m;
    cin >> n >> m;

    vector<vector<Edge>> graph(n + 1);
    for (int i = 0; i < n - 1; ++i) {
        int u, v, w;
        cin >> u >> v >> w;
        graph[u].push_back({v, w});
        graph[v].push_back({u, w});
    }

    vector<pair<int, int>> plans(m);
    for (int i = 0; i < m; ++i) {
        cin >> plans[i].first >> plans[i].second;
    }

    int min_max_time = INF;
    for (int hole = 1; hole <= n; ++hole) {
        int max_time = 0;
        for (const auto& plan : plans) {
            vector<int> dist_start = dijkstra(plan.first, graph, hole);
            vector<int> dist_end = dijkstra(plan.second, graph, hole);
            max_time = max(max_time, min(dist_start[plan.second], dist_end[plan.first]));
        }
        min_max_time = min(min_max_time, max_time);
    }

    cout << min_max_time << endl;

    return 0;
}
