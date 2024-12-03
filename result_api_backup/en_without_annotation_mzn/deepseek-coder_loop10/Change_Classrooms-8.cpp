#include <iostream>
#include <vector>
#include <queue>
#include <limits>
#include <algorithm>

using namespace std;

typedef pair<int, int> pii;

const int INF = numeric_limits<int>::max();

vector<int> dijkstra(int start, const vector<vector<pii>>& graph) {
    int n = graph.size();
    vector<int> dist(n, INF);
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

    vector<int> C(n), D(n);
    vector<float> K(n);
    for (int i = 0; i < n; ++i) cin >> C[i];
    for (int i = 0; i < n; ++i) cin >> D[i];
    for (int i = 0; i < n; ++i) cin >> K[i];

    vector<vector<pii>> graph(v + 1);
    for (int i = 0; i < e; ++i) {
        int a, b, w;
        cin >> a >> b >> w;
        graph[a].push_back({b, w});
        graph[b].push_back({a, w});
    }

    vector<vector<int>> distC(n, vector<int>(v + 1));
    vector<vector<int>> distD(n, vector<int>(v + 1));

    for (int i = 0; i < n; ++i) {
        distC[i] = dijkstra(C[i], graph);
        distD[i] = dijkstra(D[i], graph);
    }

    vector<vector<float>> dp(n, vector<float>(m + 1, INF));
    dp[0][0] = 0;

    for (int i = 1; i < n; ++i) {
        for (int j = 0; j <= m; ++j) {
            if (dp[i - 1][j] == INF) continue;

            dp[i][j] = min(dp[i][j], dp[i - 1][j] + distC[i - 1][C[i]]);

            if (j < m) {
                dp[i][j + 1] = min(dp[i][j + 1], dp[i - 1][j] + distD[i - 1][C[i]] * K[i - 1] + distC[i - 1][D[i]] * (1 - K[i - 1]));
                dp[i][j + 1] = min(dp[i][j + 1], dp[i - 1][j] + distC[i - 1][D[i]] * (1 - K[i - 1]) + distD[i - 1][C[i]] * K[i - 1]);
                dp[i][j + 1] = min(dp[i][j + 1], dp[i - 1][j] + distD[i - 1][D[i]] * K[i - 1] * K[i - 1]);
            }
        }
    }

    float min_cost = INF;
    for (int j = 0; j <= m; ++j) {
        min_cost = min(min_cost, dp[n - 1][j]);
    }

    cout << fixed << setprecision(2) << min_cost << endl;

    return 0;
}
