#include <iostream>
#include <vector>
#include <queue>
#include <limits>

using namespace std;

const int INF = numeric_limits<int>::max();

struct Edge {
    int to, dist;
    Edge(int to, int dist) : to(to), dist(dist) {}
};

struct State {
    int node, dist, color_mask;
    State(int node, int dist, int color_mask) : node(node), dist(dist), color_mask(color_mask) {}
    bool operator>(const State& other) const {
        return dist > other.dist;
    }
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

    vector<vector<Edge>> graph(N + 1);
    for (int i = 0; i < M; ++i) {
        int u, v, d;
        cin >> u >> v >> d;
        graph[u].emplace_back(v, d);
        graph[v].emplace_back(u, d);
    }

    priority_queue<State, vector<State>, greater<State>> pq;
    vector<vector<int>> dist(N + 1, vector<int>(1 << K, INF));
    pq.emplace(S, 0, 1 << (C[S] - 1));
    dist[S][1 << (C[S] - 1)] = 0;

    while (!pq.empty()) {
        State curr = pq.top();
        pq.pop();
        int u = curr.node, d = curr.dist, mask = curr.color_mask;

        if (u == T) {
            cout << "dist=" << d << endl;
            return 0;
        }

        for (const Edge& e : graph[u]) {
            int v = e.to, new_dist = d + e.dist;
            int new_mask = mask | (1 << (C[v] - 1));

            if ((mask & (1 << (C[v] - 1))) == 0 && A[C[u]][C[v]] == 0 && new_dist < dist[v][new_mask]) {
                dist[v][new_mask] = new_dist;
                pq.emplace(v, new_dist, new_mask);
            }
        }
    }

    cout << "dist=INF" << endl;
    return 0;
}
