#include <iostream>
#include <vector>
#include <queue>
#include <limits>
#include <algorithm>

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
    priority_queue<pair<int, pair<int, int>>, vector<pair<int, pair<int, int>>>, greater<pair<int, pair<int, int>>>> pq;
    pq.push({0, {S, 1 << (C[S] - 1)}});
    dist[S][1 << (C[S] - 1)] = 0;

    while (!pq.empty()) {
        auto [d, state] = pq.top();
        pq.pop();
        int u = state.first, mask = state.second;

        if (u == T) {
            cout << "dist=" << d << endl;
            return 0;
        }

        for (auto& edge : graph[u]) {
            int v = edge.to, cost = edge.cost;
            int new_mask = mask | (1 << (C[v] - 1));
            if (A[C[u]][C[v]] == 0 && (mask & (1 << (C[v] - 1))) == 0 && dist[v][new_mask] > d + cost) {
                dist[v][new_mask] = d + cost;
                pq.push({d + cost, {v, new_mask}});
            }
        }
    }

    cout << "dist=INF" << endl;
    return 0;
}
