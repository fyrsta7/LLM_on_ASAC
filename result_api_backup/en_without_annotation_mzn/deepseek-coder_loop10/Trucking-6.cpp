#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

typedef pair<int, int> pii;

vector<vector<pii>> adj;
vector<int> weight;
vector<int> start, end;
vector<int> truck;

void dijkstra(int s, int e, int qi) {
    int n = adj.size();
    vector<int> dist(n, INT_MAX);
    vector<int> min_weight(n, INT_MAX);
    priority_queue<pii, vector<pii>, greater<pii>> pq;

    dist[s] = 0;
    pq.push({0, s});

    while (!pq.empty()) {
        int u = pq.top().second;
        pq.pop();

        for (auto &edge : adj[u]) {
            int v = edge.first;
            int w = edge.second;

            int new_dist = dist[u] + 1;
            int new_min_weight = min(min_weight[u], weight[w]);

            if (new_dist < dist[v] || (new_dist == dist[v] && new_min_weight > min_weight[v])) {
                dist[v] = new_dist;
                min_weight[v] = new_min_weight;
                pq.push({dist[v], v});
            }
        }
    }

    if (dist[e] != INT_MAX) {
        truck[qi] = min_weight[e];
    }
}

int main() {
    int n, m, q;
    cin >> n >> m;

    adj.resize(n + 1);
    weight.resize(m + 1);
    start.resize(q + 1);
    end.resize(q + 1);
    truck.resize(q + 1, -1);

    for (int i = 1; i <= m; ++i) {
        int x, y, w;
        cin >> x >> y >> w;
        adj[x].push_back({y, i});
        adj[y].push_back({x, i});
        weight[i] = w;
    }

    cin >> q;
    for (int i = 1; i <= q; ++i) {
        cin >> start[i] >> end[i];
        dijkstra(start[i], end[i], i);
    }

    for (int i = 1; i <= q; ++i) {
        cout << truck[i] << endl;
    }

    return 0;
}
