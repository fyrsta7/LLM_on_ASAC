#include <iostream>
#include <vector>
#include <queue>
#include <limits>
#include <algorithm>

using namespace std;

const int INF = numeric_limits<int>::max();

struct Edge {
    int to, weight;
};

struct State {
    int node, color, dist;
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

    vector<int> U(M + 1), V(M + 1), D(M + 1);
    for (int i = 1; i <= M; ++i) cin >> U[i] >> V[i] >> D[i];

    vector<vector<Edge>> graph(N + 1);
    for (int i = 1; i <= M; ++i) {
        graph[U[i]].push_back({V[i], D[i]});
        graph[V[i]].push_back({U[i], D[i]});
    }

    vector<vector<int>> dist(N + 1, vector<int>(K + 1, INF));
    priority_queue<State, vector<State>, greater<State>> pq;

    pq.push({S, C[S], 0});
    dist[S][C[S]] = 0;

    while (!pq.empty()) {
        State curr = pq.top();
        pq.pop();

        if (curr.node == T) {
            cout << "dist=" << curr.dist << endl;
            return 0;
        }

        for (const Edge& e : graph[curr.node]) {
            int next_node = e.to;
            int next_color = C[next_node];
            int next_dist = curr.dist + e.weight;

            if (A[curr.color][next_color] == 0 && next_dist < dist[next_node][next_color]) {
                dist[next_node][next_color] = next_dist;
                pq.push({next_node, next_color, next_dist});
            }
        }
    }

    cout << "dist=INF" << endl;
    return 0;
}
