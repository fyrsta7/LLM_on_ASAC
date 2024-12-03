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
    vector<int> dist(n + 1, INF);
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    dist[start] = 0;
    pq.push({0, start});

    while (!pq.empty()) {
        int u = pq.top().second;
        int d = pq.top().first;
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

    vector<int> C(n + 1), D(n + 1);
    vector<double> K(n + 1);

    for (int i = 1; i <= n; ++i) cin >> C[i];
    for (int i = 1; i <= n; ++i) cin >> D[i];
    for (int i = 1; i <= n; ++i) cin >> K[i];

    graph.resize(v + 1);

    for (int i = 0; i < e; ++i) {
        int a, b, w;
        cin >> a >> b >> w;
        addEdge(a, b, w);
    }

    vector<vector<int>> distCC(n + 1, vector<int>(n + 1, INF));
    vector<vector<int>> distDC(n + 1, vector<int>(n + 1, INF));
    vector<vector<int>> distCD(n + 1, vector<int>(n + 1, INF));
    vector<vector<int>> distDD(n + 1, vector<int>(n + 1, INF));

    for (int i = 1; i <= n; ++i) {
        distCC[i] = dijkstra(C[i], v);
        distDC[i] = dijkstra(D[i], v);
    }

    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) {
            distCD[i][j] = distCC[i][D[j]];
            distDD[i][j] = distDC[i][D[j]];
        }
    }

    vector<vector<double>> dp(n + 1, vector<double>(m + 1, INF));
    dp[0][0] = 0;

    for (int i = 1; i <= n; ++i) {
        for (int j = 0; j <= m; ++j) {
            if (j > 0) {
                dp[i][j] = min(dp[i][j], dp[i - 1][j - 1] + distDC[i - 1][C[i]] * K[i - 1] + distCC[i - 1][C[i]] * (1 - K[i - 1]));
                dp[i][j] = min(dp[i][j], dp[i - 1][j - 1] + distDD[i - 1][D[i]] * K[i - 1] * K[i] + distCD[i - 1][D[i]] * K[i - 1] * (1 - K[i]) + distDC[i - 1][C[i]] * (1 - K[i - 1]) * K[i] + distCC[i - 1][C[i]] * (1 - K[i - 1]) * (1 - K[i]));
            }
            dp[i][j] = min(dp[i][j], dp[i - 1][j] + distCC[i - 1][C[i]]);
        }
    }

    double minCost = INF;
    for (int j = 0; j <= m; ++j) {
        minCost = min(minCost, dp[n][j]);
    }

    cout << fixed << setprecision(2) << minCost << endl;

    return 0;
}
