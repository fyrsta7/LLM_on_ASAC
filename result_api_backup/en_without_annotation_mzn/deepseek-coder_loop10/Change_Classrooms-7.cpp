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
vector<int> dist;

void dijkstra(int start) {
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
            int weight = e.weight;

            if (dist[u] + weight < dist[v]) {
                dist[v] = dist[u] + weight;
                pq.push({dist[v], v});
            }
        }
    }
}

int main() {
    int n, m, v, e;
    cin >> n >> m >> v >> e;

    vector<int> C(n), D(n);
    vector<float> K(n);
    for (int i = 0; i < n; ++i) cin >> C[i];
    for (int i = 0; i < n; ++i) cin >> D[i];
    for (int i = 0; i < n; ++i) cin >> K[i];

    graph.resize(v + 1);
    for (int i = 0; i < e; ++i) {
        int a, b, w;
        cin >> a >> b >> w;
        graph[a].emplace_back(b, w);
        graph[b].emplace_back(a, w);
    }

    vector<vector<int>> distC(n, vector<int>(v + 1, INF));
    vector<vector<int>> distD(n, vector<int>(v + 1, INF));

    for (int i = 0; i < n; ++i) {
        dist.assign(v + 1, INF);
        dijkstra(C[i]);
        distC[i] = dist;

        dist.assign(v + 1, INF);
        dijkstra(D[i]);
        distD[i] = dist;
    }

    vector<vector<float>> dp(n, vector<float>(m + 1, INF));
    dp[0][0] = 0;

    for (int i = 1; i < n; ++i) {
        for (int j = 0; j <= m; ++j) {
            if (dp[i - 1][j] == INF) continue;

            float pcc = distC[i - 1][C[i]];
            float pdc = distD[i - 1][C[i]];
            float pcd = distC[i - 1][D[i]];
            float pdd = distD[i - 1][D[i]];

            dp[i][j] = min(dp[i][j], dp[i - 1][j] + pcc);

            if (j > 0) {
                dp[i][j] = min(dp[i][j], dp[i - 1][j - 1] + pdc * K[i - 1] + pcc * (1 - K[i - 1]));
                dp[i][j] = min(dp[i][j], dp[i - 1][j - 1] + pcd * K[i] + pcc * (1 - K[i]));
                dp[i][j] = min(dp[i][j], dp[i - 1][j - 1] + pdd * K[i - 1] * K[i] + pdc * K[i - 1] * (1 - K[i]) + pcd * (1 - K[i - 1]) * K[i] + pcc * (1 - K[i - 1]) * (1 - K[i]));
            }
        }
    }

    float min_obj = INF;
    for (int j = 0; j <= m; ++j) {
        min_obj = min(min_obj, dp[n - 1][j]);
    }

    cout << fixed << setprecision(2) << min_obj << endl;

    return 0;
}
