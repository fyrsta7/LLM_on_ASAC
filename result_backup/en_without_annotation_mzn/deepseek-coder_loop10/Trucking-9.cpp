#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

const int INF = 1e9;

struct Edge {
    int to, weight;
};

vector<vector<Edge>> adj;
vector<int> dist, parent, path;

void dijkstra(int start, int n) {
    dist.assign(n + 1, INF);
    parent.assign(n + 1, -1);
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    dist[start] = 0;
    pq.push({0, start});

    while (!pq.empty()) {
        int u = pq.top().second;
        int d = pq.top().first;
        pq.pop();

        if (d > dist[u]) continue;

        for (const Edge &e : adj[u]) {
            int v = e.to;
            int w = e.weight;
            if (dist[u] + w < dist[v]) {
                dist[v] = dist[u] + w;
                parent[v] = u;
                pq.push({dist[v], v});
            }
        }
    }
}

void getPath(int end) {
    path.clear();
    for (int v = end; v != -1; v = parent[v]) {
        path.push_back(v);
    }
    reverse(path.begin(), path.end());
}

int main() {
    int n, m;
    cin >> n >> m;
    adj.resize(n + 1);
    vector<int> x(m), y(m), weight(m);
    for (int i = 0; i < m; ++i) {
        cin >> x[i] >> y[i] >> weight[i];
        adj[x[i]].push_back({y[i], weight[i]});
        adj[y[i]].push_back({x[i], weight[i]});
    }

    int q;
    cin >> q;
    vector<int> start(q), end(q);
    for (int i = 0; i < q; ++i) {
        cin >> start[i] >> end[i];
    }

    for (int i = 0; i < q; ++i) {
        dijkstra(start[i], n);
        if (dist[end[i]] == INF) {
            cout << "-1\n";
        } else {
            getPath(end[i]);
            int minWeight = INF;
            for (int j = 0; j < path.size() - 1; ++j) {
                int u = path[j];
                int v = path[j + 1];
                for (const Edge &e : adj[u]) {
                    if (e.to == v) {
                        minWeight = min(minWeight, e.weight);
                        break;
                    }
                }
            }
            cout << minWeight << "\n";
        }
    }

    return 0;
}
