#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <climits>

using namespace std;

typedef pair<int, int> pii;

vector<int> dijkstra(int n, int start, const vector<vector<pii>>& adj) {
    vector<int> dist(n, INT_MAX);
    priority_queue<pii, vector<pii>, greater<pii>> pq;
    dist[start] = 0;
    pq.push({0, start});

    while (!pq.empty()) {
        int u = pq.top().second;
        int d = pq.top().first;
        pq.pop();

        if (d > dist[u]) continue;

        for (auto& edge : adj[u]) {
            int v = edge.first;
            int weight = edge.second;
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
    vector<int> x(m), y(m), weight(m);
    for (int i = 0; i < m; ++i) {
        cin >> x[i] >> y[i] >> weight[i];
        x[i]--; y[i]--;
    }

    int q;
    cin >> q;
    vector<int> start(q), end(q);
    for (int i = 0; i < q; ++i) {
        cin >> start[i] >> end[i];
        start[i]--; end[i]--;
    }

    vector<vector<pii>> adj(n);
    for (int i = 0; i < m; ++i) {
        adj[x[i]].push_back({y[i], weight[i]});
        adj[y[i]].push_back({x[i], weight[i]});
    }

    for (int i = 0; i < q; ++i) {
        if (start[i] == end[i]) {
            cout << "0\n";
            continue;
        }

        vector<int> dist = dijkstra(n, start[i], adj);
        if (dist[end[i]] == INT_MAX) {
            cout << "-1\n";
            continue;
        }

        vector<int> path;
        int cur = end[i];
        while (cur != start[i]) {
            path.push_back(cur);
            for (auto& edge : adj[cur]) {
                int v = edge.first;
                int w = edge.second;
                if (dist[v] + w == dist[cur]) {
                    cur = v;
                    break;
                }
            }
        }
        path.push_back(start[i]);
        reverse(path.begin(), path.end());

        int min_weight = INT_MAX;
        for (int j = 0; j < path.size() - 1; ++j) {
            int u = path[j];
            int v = path[j + 1];
            for (auto& edge : adj[u]) {
                if (edge.first == v) {
                    min_weight = min(min_weight, edge.second);
                    break;
                }
            }
        }

        cout << min_weight << "\n";
    }

    return 0;
}
