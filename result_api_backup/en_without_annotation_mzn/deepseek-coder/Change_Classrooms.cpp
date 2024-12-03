#include <iostream>
#include <vector>
#include <queue>
#include <limits>
#include <algorithm>

using namespace std;

typedef pair<int, int> pii;

const int INF = numeric_limits<int>::max();

vector<int> dijkstra(int n, int v, const vector<vector<pii>>& graph, int start) {
    vector<int> dist(v + 1, INF);
    priority_queue<pii, vector<pii>, greater<pii>> pq;
    dist[start] = 0;
    pq.push({0, start});

    while (!pq.empty()) {
        int u = pq.top().second;
        int d = pq.top().first;
        pq.pop();

        if (d > dist[u]) continue;

        for (const auto& edge : graph[u]) {
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
    int n, m, v, e;
    cin >> n >> m >> v >> e;

    vector<int> C(n + 1), D(n + 1);
    vector<double> K(n + 1);
    vector<vector<pii>> graph(v + 1);

    for (int i = 1; i <= n; ++i) cin >> C[i];
    for (int i = 1; i <= n; ++i) cin >> D[i];
    for (int i = 1; i <= n; ++i) cin >> K[i];

    for (int i = 0; i < e; ++i) {
        int a, b, w;
        cin >> a >> b >> w;
        graph[a].push_back({b, w});
        graph[b].push_back({a, w});
    }

    vector<vector<int>> distC(n + 1, vector<int>(v + 1));
    vector<vector<int>> distD(n + 1, vector<int>(v + 1));

    for (int i = 1; i <= n; ++i) {
        distC[i] = dijkstra(n, v, graph, C[i]);
        distD[i] = dijkstra(n, v, graph, D[i]);
    }

    vector<vector<double>> dp(n + 1, vector<double>(m + 1, INF));
    dp[0][0] = 0;

    for (int i = 1; i <= n; ++i) {
        for (int j = 0; j <= m; ++j) {
            if (dp[i - 1][j] == INF) continue;

            double pcc = distC[i - 1][C[i]];
            double pdc = distD[i - 1][C[i]];
            double pcd = distC[i - 1][D[i]];
            double pdd = distD[i - 1][D[i]];

            dp[i][j] = min(dp[i][j], dp[i - 1][j] + pcc);

            if (j > 0) {
                dp[i][j] = min(dp[i][j], dp[i - 1][j - 1] + pdc * K[i - 1] + pcc * (1 - K[i - 1]));
                dp[i][j] = min(dp[i][j], dp[i - 1][j - 1] + pcd * K[i] + pcc * (1 - K[i]));
                dp[i][j] = min(dp[i][j], dp[i - 1][j - 1] + pdd * K[i - 1] * K[i] + pdc * K[i - 1] * (1 - K[i]) + pcd * (1 - K[i - 1]) * K[i] + pcc * (1 - K[i - 1]) * (1 - K[i]));
            }
        }
    }

    double min_cost = INF;
    for (int j = 0; j <= m; ++j) {
        min_cost = min(min_cost, dp[n][j]);
    }

    cout << fixed << setprecision(2) << min_cost << endl;

    return 0;
}
