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

vector<int> dijkstra(int n, const vector<vector<Edge>>& graph, int start) {
    vector<int> dist(n, INF);
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    dist[start] = 0;
    pq.push({0, start});

    while (!pq.empty()) {
        int cost = pq.top().first;
        int node = pq.top().second;
        pq.pop();

        if (cost > dist[node]) continue;

        for (const auto& edge : graph[node]) {
            int new_cost = cost + edge.cost;
            if (new_cost < dist[edge.to]) {
                dist[edge.to] = new_cost;
                pq.push({new_cost, edge.to});
            }
        }
    }

    return dist;
}

int main() {
    int n, m;
    cin >> n >> m;

    vector<vector<Edge>> graph(n);
    vector<vector<Edge>> reverse_graph(n);

    for (int i = 0; i < n - 1; ++i) {
        int u, v, w;
        cin >> u >> v >> w;
        --u; --v;
        graph[u].push_back({v, w});
        graph[v].push_back({u, w});
        reverse_graph[u].push_back({v, w});
        reverse_graph[v].push_back({u, w});
    }

    vector<pair<int, int>> plans(m);
    for (int i = 0; i < m; ++i) {
        cin >> plans[i].first >> plans[i].second;
        --plans[i].first; --plans[i].second;
    }

    int min_max_time = INF;

    for (int hole = 0; hole < n - 1; ++hole) {
        vector<vector<Edge>> temp_graph = graph;
        for (auto& edges : temp_graph) {
            edges.erase(remove_if(edges.begin(), edges.end(), [&](const Edge& e) { return e.to == hole; }), edges.end());
        }

        int max_time = 0;
        for (const auto& plan : plans) {
            vector<int> dist = dijkstra(n, temp_graph, plan.first);
            max_time = max(max_time, dist[plan.second]);
        }

        min_max_time = min(min_max_time, max_time);
    }

    cout << min_max_time << endl;

    return 0;
}
