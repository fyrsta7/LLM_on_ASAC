#include <iostream>
#include <vector>
#include <queue>
#include <limits>

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

    vector<vector<Edge>> graph(N + 1);
    for (int i = 0; i < M; ++i) {
        int u, v, d;
        cin >> u >> v >> d;
        graph[u].push_back({v, d});
        graph[v].push_back({u, d});
    }

    vector<vector<int>> dist(N + 1, vector<int>(K + 1, INF));
    priority_queue<State, vector<State>, greater<State>> pq;

    pq.push({S, C[S], 0});
    dist[S][C[S]] = 0;

    while (!pq.empty()) {
        State curr = pq.top();
        pq.pop();

        if (curr.dist > dist[curr.node][curr.color]) continue;

        for (const Edge& e : graph[curr.node]) {
            int nextColor = C[e.to];
            if (A[curr.color][nextColor] == 0 && dist[e.to][nextColor] > curr.dist + e.weight) {
                dist[e.to][nextColor] = curr.dist + e.weight;
                pq.push({e.to, nextColor, dist[e.to][nextColor]});
            }
        }
    }

    int minDist = INF;
    for (int i = 1; i <= K; ++i) {
        if (dist[T][i] < minDist) {
            minDist = dist[T][i];
        }
    }

    cout << "dist=" << (minDist == INF ? -1 : minDist) << endl;

    return 0;
}