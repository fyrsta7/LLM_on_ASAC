#include <iostream>
#include <vector>
#include <queue>
#include <limits>
#include <algorithm>

using namespace std;

const int INF = numeric_limits<int>::max();

struct Edge {
    int to, weight;
    Edge(int t, int w) : to(t), weight(w) {}
};

vector<vector<Edge>> graph;

void addEdge(int u, int v, int w) {
    graph[u].emplace_back(v, w);
    graph[v].emplace_back(u, w);
}

vector<int> dijkstra(int start, int n) {
    vector<int> dist(n, INF);
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    dist[start] = 0;
    pq.push({0, start});

    while (!pq.empty()) {
        int d = pq.top().first;
        int u = pq.top().second;
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
    int n, m, v, e;
    cin >> n >> m >> v >> e;

    vector<int> C(n), D(n);
    vector<double> K(n);

    for (int i = 0; i < n; ++i) cin >> C[i];
    for (int i = 0; i < n; ++i) cin >> D[i];
    for (int i = 0; i < n; ++i) cin >> K[i];

    graph.resize(v + 1);

    for (int i = 0; i < e; ++i) {
        int a, b, w;
        cin >> a >> b >> w;
        addEdge(a, b, w);
    }

    vector<vector<int>> distC(n), distD(n);
    for (int i = 0; i < n; ++i) {
        distC[i] = dijkstra(C[i], v + 1);
        distD[i] = dijkstra(D[i], v + 1);
    }

    double obj = 0.0;
    for (int i = 0; i < n - 1; ++i) {
        int pcc = distC[i][C[i + 1]];
        int pdc = distD[i][C[i + 1]];
        int pcd = distC[i][D[i + 1]];
        int pdd = distD[i][D[i + 1]];

        double minCost = pcc;
        minCost = min(minCost, pcc * (1 - K[i]) * (1 - K[i + 1]) + pdc * K[i] * (1 - K[i + 1]) + pcd * K[i + 1] * (1 - K[i]) + pdd * K[i] * K[i + 1]);
        minCost = min(minCost, pcc * (1 - K[i + 1]) + pcd * K[i + 1]);
        minCost = min(minCost, pcc * (1 - K[i]) + pdc * K[i]);

        obj += minCost;
    }

    cout << fixed << setprecision(2) << obj << endl;

    return 0;
}
