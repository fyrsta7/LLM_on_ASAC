#include <iostream>
#include <vector>
#include <queue>
#include <limits>

using namespace std;

const int INF = numeric_limits<int>::max();

struct Edge {
    int to, dist;
    Edge(int t, int d) : to(t), dist(d) {}
};

struct State {
    int node, color, dist;
    State(int n, int c, int d) : node(n), color(c), dist(d) {}
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
    
    vector<vector<Edge>> adj(N + 1);
    for (int i = 0; i < M; ++i) {
        int u, v, d;
        cin >> u >> v >> d;
        adj[u].emplace_back(v, d);
        adj[v].emplace_back(u, d);
    }
    
    priority_queue<State, vector<State>, greater<State>> pq;
    vector<vector<int>> dist(N + 1, vector<int>(K + 1, INF));
    
    pq.emplace(S, C[S], 0);
    dist[S][C[S]] = 0;
    
    while (!pq.empty()) {
        State curr = pq.top();
        pq.pop();
        
        if (curr.node == T) {
            cout << "dist=" << curr.dist << endl;
            return 0;
        }
        
        for (const Edge& e : adj[curr.node]) {
            int next_color = C[e.to];
            if (A[curr.color][next_color] == 0 && dist[e.to][next_color] > curr.dist + e.dist) {
                dist[e.to][next_color] = curr.dist + e.dist;
                pq.emplace(e.to, next_color, dist[e.to][next_color]);
            }
        }
    }
    
    cout << "dist=INF" << endl;
    return 0;
}
