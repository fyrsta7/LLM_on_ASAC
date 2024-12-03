#include <iostream>
#include <vector>
#include <queue>
#include <limits>
#include <algorithm>

using namespace std;

typedef pair<int, int> pii;

const int INF = numeric_limits<int>::max();

vector<int> dijkstra(int n, int start, const vector<vector<pii>>& adj) {
    vector<int> dist(n + 1, INF);
    priority_queue<pii, vector<pii>, greater<pii>> pq;
    dist[start] = 0;
    pq.push({0, start});

    while (!pq.empty()) {
        int u = pq.top().second;
        int d = pq.top().first;
        pq.pop();

        if (d > dist[u]) continue;

        for (const auto& edge : adj[u]) {
            int v = edge.first;
            int w = edge.second;

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

    vector<vector<pii>> adj(v + 1);

    for (int i = 0; i < e; ++i) {
        int a, b, w;
        cin >> a >> b >> w;
        adj[a].push_back({b, w});
        adj[b].push_back({a, w});
    }

    vector<vector<int>> dist(n + 1, vector<int>(v + 1, INF));

    for (int i = 1; i <= n; ++i) {
        dist[i] = dijkstra(v, C[i], adj);
    }

    vector<vector<int>> distD(n + 1, vector<int>(v + 1, INF));

    for (int i = 1; i <= n; ++i) {
        distD[i] = dijkstra(v, D[i], adj);
    }

    vector<vector<double>> dp(n + 1, vector<double>(m + 1, INF));
    dp[0][0] = 0;

    for (int i = 1; i <= n; ++i) {
        for (int j = 0; j <= m; ++j) {
            if (j > 0) {
                dp[i][j] = min(dp[i][j], dp[i - 1][j - 1] + distD[i - 1][D[i]] * K[i - 1] * K[i] + distD[i - 1][C[i]] * K[i - 1] * (1 - K[i]) + dist[i - 1][D[i]] * (1 - K[i - 1]) * K[i] + dist[i - 1][C[i]] * (1 - K[i - 1]) * (1 - K[i]));
            }
            dp[i][j] = min(dp[i][j], dp[i - 1][j] + dist[i - 1][C[i]]);
        }
    }

    double ans = INF;
    for (int j = 0; j <= m; ++j) {
        ans = min(ans, dp[n][j]);
    }

    cout << fixed << setprecision(2) << ans << endl;

    return 0;
}
