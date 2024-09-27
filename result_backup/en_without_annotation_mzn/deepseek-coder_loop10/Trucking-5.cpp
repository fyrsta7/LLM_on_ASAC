#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <climits>

using namespace std;

struct Edge {
    int to, weight;
};

vector<int> dijkstra(int n, const vector<vector<Edge>>& graph, int start) {
    vector<int> dist(n, INT_MAX);
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
    int n, m;
    cin >> n >> m;

    vector<int> x(m), y(m), weight(m);
    vector<vector<Edge>> graph(n);

    for (int i = 0; i < m; ++i) {
        cin >> x[i] >> y[i] >> weight[i];
        graph[x[i] - 1].push_back({y[i] - 1, weight[i]});
        graph[y[i] - 1].push_back({x[i] - 1, weight[i]});
    }

    int q;
    cin >> q;
    vector<int> start(q), end(q);

    for (int i = 0; i < q; ++i) {
        cin >> start[i] >> end[i];
        --start[i];
        --end[i];
    }

    vector<vector<int>> dist(n, vector<int>(n, INT_MAX));

    for (int i = 0; i < n; ++i) {
        dist[i] = dijkstra(n, graph, i);
    }

    for (int i = 0; i < q; ++i) {
        if (dist[start[i]][end[i]] == INT_MAX) {
            cout << "-1\n";
        } else {
            int min_weight = INT_MAX;
            for (const Edge& e : graph[start[i]]) {
                if (dist[e.to][end[i]] + e.weight == dist[start[i]][end[i]]) {
                    min_weight = min(min_weight, e.weight);
                }
            }
            cout << min_weight << "\n";
        }
    }

    return 0;
}
