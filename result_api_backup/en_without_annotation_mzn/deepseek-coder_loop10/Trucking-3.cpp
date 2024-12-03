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
    for (int i = 0; i < m; ++i) {
        cin >> x[i] >> y[i] >> weight[i];
        --x[i]; --y[i];
    }

    int q;
    cin >> q;
    vector<int> start(q), end(q);
    for (int i = 0; i < q; ++i) {
        cin >> start[i] >> end[i];
        --start[i]; --end[i];
    }

    vector<vector<Edge>> graph(n);
    for (int i = 0; i < m; ++i) {
        graph[x[i]].push_back({y[i], weight[i]});
        graph[y[i]].push_back({x[i], weight[i]});
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
            vector<int> path;
            int current = end[i];
            while (current != start[i]) {
                path.push_back(current);
                for (const Edge& e : graph[current]) {
                    if (dist[e.to] + e.weight == dist[current]) {
                        current = e.to;
                        break;
                    }
                }
            }
            path.push_back(start[i]);
            reverse(path.begin(), path.end());

            int min_weight = INT_MAX;
            for (int j = 0; j < path.size() - 1; ++j) {
                for (const Edge& e : graph[path[j]]) {
                    if (e.to == path[j + 1]) {
                        min_weight = min(min_weight, e.weight);
                        break;
                    }
                }
            }
            cout << min_weight << "\n";
        }
    }

    return 0;
}
