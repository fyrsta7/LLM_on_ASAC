#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <limits>

using namespace std;

typedef pair<int, int> pii;

const int INF = numeric_limits<int>::max();

vector<int> dijkstra(int n, int start, const vector<vector<pii>>& graph, int hole) {
    vector<int> dist(n, INF);
    priority_queue<pii, vector<pii>, greater<pii>> pq;
    dist[start] = 0;
    pq.push({0, start});

    while (!pq.empty()) {
        int u = pq.top().second;
        int d = pq.top().first;
        pq.pop();

        if (d > dist[u]) continue;

        for (const auto& edge : graph[u]) {
            int v = edge.first;
            int weight = edge.second;
            if (u == hole && v == hole) continue;
            if (dist[u] + weight < dist[v]) {
                dist[v] = dist[u] + weight;
                pq.push({dist[v], v});
            }
        }
    }

    return dist;
}

int main() {
    int n, m;
    cin >> n >> m;

    vector<vector<pii>> graph(n);
    for (int i = 0; i < n - 1; ++i) {
        int u, v, w;
        cin >> u >> v >> w;
        graph[u - 1].push_back({v - 1, w});
        graph[v - 1].push_back({u - 1, w});
    }

    vector<pii> plans(m);
    for (int i = 0; i < m; ++i) {
        cin >> plans[i].first >> plans[i].second;
        plans[i].first--;
        plans[i].second--;
    }

    int min_max_time = INF;
    for (int hole = 0; hole < n; ++hole) {
        int max_time = 0;
        for (const auto& plan : plans) {
            vector<int> dist = dijkstra(n, plan.first, graph, hole);
            max_time = max(max_time, dist[plan.second]);
        }
        min_max_time = min(min_max_time, max_time);
    }

    cout << min_max_time << endl;

    return 0;
}