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

    vector<vector<Edge>> graph(n);
    for (int i = 0; i < m; ++i) {
        int x, y, weight;
        cin >> x >> y >> weight;
        --x; --y;
        graph[x].push_back({y, weight});
        graph[y].push_back({x, weight});
    }

    int q;
    cin >> q;
    vector<int> start(q), end(q);
    for (int i = 0; i < q; ++i) {
        cin >> start[i] >> end[i];
        --start[i]; --end[i];
    }

    for (int i = 0; i < q; ++i) {
        if (start[i] == end[i]) {
            cout << "0\n";
            continue;
        }

        vector<int> dist = dijkstra(n, graph, start[i]);
        if (dist[end[i]] == INT_MAX) {
            cout << "-1\n";
        } else {
            vector<int> dist_end = dijkstra(n, graph, end[i]);
            int min_weight = INT_MAX;
            for (int u = 0; u < n; ++u) {
                for (const Edge& e : graph[u]) {
                    int v = e.to;
                    if (dist[u] + e.weight + dist_end[v] == dist[end[i]]) {
                        min_weight = min(min_weight, e.weight);
                    }
                }
            }
            cout << min_weight << "\n";
        }
    }

    return 0;
}
