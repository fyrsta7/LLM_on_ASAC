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

        for (const Edge &e : graph[u]) {
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

    vector<vector<double>> dp(n, vector<double>(m + 1, INF));
    dp[0][0] = 0;

    for (int i = 1; i < n; ++i) {
        for (int j = 0; j <= m; ++j) {
            if (dp[i - 1][j] == INF) continue;

            // No change
            dp[i][j] = min(dp[i][j], dp[i - 1][j] + distC[i - 1][C[i]]);

            // Change current
            if (j < m) {
                dp[i][j + 1] = min(dp[i][j + 1], dp[i - 1][j] + distD[i - 1][C[i]] * K[i - 1] + distC[i - 1][D[i]] * (1 - K[i - 1]));
            }

            // Change next
            if (j < m) {
                dp[i][j + 1] = min(dp[i][j + 1], dp[i - 1][j] + distC[i - 1][D[i]] * K[i] + distD[i - 1][C[i]] * (1 - K[i]));
            }

            // Change both
            if (j < m - 1) {
                dp[i][j + 2] = min(dp[i][j + 2], dp[i - 1][j] + distD[i - 1][D[i]] * K[i - 1] * K[i] + distD[i - 1][C[i]] * K[i - 1] * (1 - K[i]) + distC[i - 1][D[i]] * (1 - K[i - 1]) * K[i] + distC[i - 1][C[i]] * (1 - K[i - 1]) * (1 - K[i]));
            }
        }
    }

    double min_cost = INF;
    for (int j = 0; j <= m; ++j) {
        min_cost = min(min_cost, dp[n - 1][j]);
    }

    cout << fixed << setprecision(2) << min_cost << endl;

    return 0;
}
