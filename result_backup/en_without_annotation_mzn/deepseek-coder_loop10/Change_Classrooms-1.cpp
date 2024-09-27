#include <iostream>
#include <vector>
#include <queue>
#include <limits>
#include <algorithm>

using namespace std;

typedef pair<int, int> pii;

const int INF = numeric_limits<int>::max();

vector<int> dijkstra(int start, const vector<vector<pii>>& graph, int v) {
    vector<int> dist(v + 1, INF);
    priority_queue<pii, vector<pii>, greater<pii>> pq;
    dist[start] = 0;
    pq.push({0, start});

    while (!pq.empty()) {
        int cost = pq.top().first;
        int cur = pq.top().second;
        pq.pop();

        if (dist[cur] < cost) continue;

        for (const auto& edge : graph[cur]) {
            int next = edge.first;
            int nextCost = cost + edge.second;

            if (dist[next] > nextCost) {
                dist[next] = nextCost;
                pq.push({nextCost, next});
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

    vector<vector<pii>> graph(v + 1);

    for (int i = 0; i < e; ++i) {
        int a, b, w;
        cin >> a >> b >> w;
        graph[a].push_back({b, w});
        graph[b].push_back({a, w});
    }

    vector<vector<int>> distC(n + 1, vector<int>(v + 1, INF));
    vector<vector<int>> distD(n + 1, vector<int>(v + 1, INF));

    for (int i = 1; i <= n; ++i) {
        distC[i] = dijkstra(C[i], graph, v);
        distD[i] = dijkstra(D[i], graph, v);
    }

    vector<vector<double>> dp(n + 1, vector<double>(m + 1, INF));
    dp[0][0] = 0;

    for (int i = 1; i <= n; ++i) {
        for (int j = 0; j <= m; ++j) {
            if (dp[i - 1][j] == INF) continue;

            double costCC = distC[i - 1][C[i]];
            double costCD = distC[i - 1][D[i]];
            double costDC = distD[i - 1][C[i]];
            double costDD = distD[i - 1][D[i]];

            dp[i][j] = min(dp[i][j], dp[i - 1][j] + costCC);

            if (j > 0) {
                dp[i][j] = min(dp[i][j], dp[i - 1][j - 1] + costCD * K[i - 1] + costCC * (1 - K[i - 1]));
                dp[i][j] = min(dp[i][j], dp[i - 1][j - 1] + costDC * K[i - 1] + costCC * (1 - K[i - 1]));
                dp[i][j] = min(dp[i][j], dp[i - 1][j - 1] + costDD * K[i - 1] * K[i] + costCD * K[i - 1] * (1 - K[i]) + costDC * (1 - K[i - 1]) * K[i] + costCC * (1 - K[i - 1]) * (1 - K[i]));
            }
        }
    }

    double minCost = INF;
    for (int j = 0; j <= m; ++j) {
        minCost = min(minCost, dp[n][j]);
    }

    cout << fixed << setprecision(2) << minCost << endl;

    return 0;
}
