#include <iostream>
#include <vector>
#include <queue>
#include <limits>

using namespace std;

const int INF = numeric_limits<int>::max();

struct Edge {
    int to, cost;
};

int main() {
    int N, K, M, S, T;
    cin >> N >> K >> M >> S >> T;

    vector<int> C(N + 1);
    for (int i = 1; i <= N; ++i) cin >> C[i];

    vector<vector<int>> A(K + 1, vector<int>(K + 1));
    for (int i = 1; i <= K; ++i)
        for (int j = 1; j <= K; ++j)
            cin >> A[i][j];

    vector<int> U(M + 1), V(M + 1), D(M + 1);
    for (int i = 1; i <= M; ++i) cin >> U[i] >> V[i] >> D[i];

    vector<vector<Edge>> graph(N + 1);
    for (int i = 1; i <= M; ++i) {
        graph[U[i]].push_back({V[i], D[i]});
        graph[V[i]].push_back({U[i], D[i]});
    }

    vector<vector<int>> dist(N + 1, vector<int>(1 << K, INF));
    priority_queue<pair<int, pair<int, int>>, vector<pair<int, pair<int, int>>>, greater<>> pq;
    pq.push({0, {S, 1 << (C[S] - 1)}});
    dist[S][1 << (C[S] - 1)] = 0;

    while (!pq.empty()) {
        auto [d, state] = pq.top();
        int u = state.first;
        int mask = state.second;
        pq.pop();

        if (d > dist[u][mask]) continue;

        for (const auto& edge : graph[u]) {
            int v = edge.to;
            int new_mask = mask | (1 << (C[v] - 1));
            if (A[C[u]][C[v]] == 0 && (mask & (1 << (C[v] - 1))) == 0) {
                if (dist[u][mask] + edge.cost < dist[v][new_mask]) {
                    dist[v][new_mask] = dist[u][mask] + edge.cost;
                    pq.push({dist[v][new_mask], {v, new_mask}});
                }
            }
        }
    }

    int min_dist = INF;
    for (int mask = 0; mask < (1 << K); ++mask) {
        min_dist = min(min_dist, dist[T][mask]);
    }

    cout << "dist=" << (min_dist == INF ? -1 : min_dist) << endl;

    return 0;
}
