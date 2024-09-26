#include <iostream>
#include <vector>
#include <queue>
#include <tuple>
#include <limits>
using namespace std;

struct Edge {
    int to, cost;
};

int main() {
    int N, K, M, S, T;
    cin >> N >> K >> M >> S >> T;
    S--; T--; // Convert to 0-indexed

    vector<int> cultures(N);
    for (int i = 0; i < N; ++i) {
        cin >> cultures[i];
        cultures[i]--; // Convert to 0-indexed
    }

    vector<vector<int>> rejection(K, vector<int>(K));
    for (int i = 0; i < K; ++i) {
        for (int j = 0; j < K; ++j) {
            cin >> rejection[i][j];
        }
    }

    vector<vector<Edge>> graph(N);
    for (int i = 0; i < M; ++i) {
        int u, v, d;
        cin >> u >> v >> d;
        u--; v--; // Convert to 0-indexed
        graph[u].push_back({v, d});
        graph[v].push_back({u, d});
    }

    // (current_node, current_cost, learned_cultures_mask)
    using State = tuple<int, int, int>;
    priority_queue<State, vector<State>, greater<State>> pq;
    vector<vector<int>> dist(N, vector<int>(1 << K, numeric_limits<int>::max()));
    
    int start_culture = cultures[S];
    pq.push({0, S, 1 << start_culture});
    dist[S][1 << start_culture] = 0;

    while (!pq.empty()) {
        auto [cur_cost, cur_node, learned_cultures] = pq.top();
        pq.pop();

        if (cur_node == T) {
            cout << cur_cost << endl;
            return 0;
        }

        for (const auto& edge : graph[cur_node]) {
            int next_node = edge.to;
            int next_culture = cultures[next_node];
            int new_learned_cultures = learned_cultures | (1 << next_culture);

            if (rejection[cultures[cur_node]][next_culture] == 0 && 
                (cur_cost + edge.cost < dist[next_node][new_learned_cultures])) {
                
                dist[next_node][new_learned_cultures] = cur_cost + edge.cost;
                pq.push({dist[next_node][new_learned_cultures], next_node, new_learned_cultures});
            }
        }
    }

    cout << -1 << endl;
    return 0;
}