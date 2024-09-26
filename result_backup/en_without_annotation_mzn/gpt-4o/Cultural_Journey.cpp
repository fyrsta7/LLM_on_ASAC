#include <iostream>
#include <vector>
#include <queue>
#include <tuple>
#include <climits>

using namespace std;

struct State {
    int node, color, cost;
    bool operator>(const State &other) const { return cost > other.cost; }
};

int main() {
    int N, K, M, S, T;
    cin >> N >> K >> M >> S >> T;
    vector<int> C(N + 1);
    vector<vector<int>> A(K + 1, vector<int>(K + 1));
    vector<tuple<int, int, int>> edges(M + 1);
    vector<vector<vector<int>>> adj(N + 1, vector<vector<int>>(K + 1));

    for (int i = 1; i <= N; ++i)
        cin >> C[i];
    for (int i = 1; i <= K; ++i)
        for (int j = 1; j <= K; ++j)
            cin >> A[i][j];
    for (int i = 1; i <= M; ++i) {
        int u, v, d;
        cin >> u >> v >> d;
        edges[i] = {u, v, d};
        adj[u][C[v]].emplace_back(i);
        adj[v][C[u]].emplace_back(i);
    }
    
    vector<vector<vector<int>>> dist(N + 1, vector<vector<int>>(K + 1, vector<int>(1 << K, INT_MAX)));
    priority_queue<State, vector<State>, greater<State>> pq;
    pq.push({S, C[S], 0});
    dist[S][C[S]][1 << C[S]] = 0;

    while (!pq.empty()) {
        auto [u, color, cost] = pq.top(); pq.pop();
        if (u == T) {
            cout << "dist=" << cost << endl;
            return 0;
        }

        for (int e : adj[u][color]) {
            auto [v, w, d] = edges[e];
            int next_color = C[v == u ? w : v];
            int next_mask = 1 << next_color;
            if ((next_mask & (1 << color)) == 0 && dist[v == u ? w : v][next_color][next_mask | (1 << color)] > cost + d) {
                dist[v == u ? w : v][next_color][next_mask | (1 << color)] = cost + d;
                pq.push({v == u ? w : v, next_color, cost + d});
            }
        }
    }

    cout << "dist=INF" << endl;
    return 0;
}