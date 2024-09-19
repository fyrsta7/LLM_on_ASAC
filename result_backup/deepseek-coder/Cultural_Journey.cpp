#include <iostream>
#include <vector>
#include <queue>
#include <limits>

using namespace std;

const int INF = numeric_limits<int>::max();

struct Edge {
    int to, dist;
};

struct State {
    int node, dist;
    vector<bool> learned;

    bool operator>(const State& other) const {
        return dist > other.dist;
    }
};

int main() {
    int N, K, M, S, T;
    cin >> N >> K >> M >> S >> T;

    vector<int> culture(N + 1);
    for (int i = 1; i <= N; ++i) {
        cin >> culture[i];
    }

    vector<vector<bool>> rejection(K + 1, vector<bool>(K + 1, false));
    for (int i = 1; i <= K; ++i) {
        for (int j = 1; j <= K; ++j) {
            int reject;
            cin >> reject;
            rejection[i][j] = (reject == 1);
        }
    }

    vector<vector<Edge>> graph(N + 1);
    for (int i = 0; i < M; ++i) {
        int u, v, d;
        cin >> u >> v >> d;
        graph[u].push_back({v, d});
        graph[v].push_back({u, d});
    }

    priority_queue<State, vector<State>, greater<State>> pq;
    vector<vector<bool>> visited(N + 1, vector<bool>(1 << K, false));
    pq.push({S, 0, vector<bool>(K + 1, false)});
    pq.top().learned[culture[S]] = true;

    while (!pq.empty()) {
        State current = pq.top();
        pq.pop();

        if (current.node == T) {
            cout << current.dist << endl;
            return 0;
        }

        if (visited[current.node][current.learned[culture[T]]]) {
            continue;
        }
        visited[current.node][current.learned[culture[T]]] = true;

        for (const Edge& edge : graph[current.node]) {
            if (current.learned[culture[edge.to]]) {
                continue;
            }
            bool canVisit = true;
            for (int i = 1; i <= K; ++i) {
                if (current.learned[i] && rejection[i][culture[edge.to]]) {
                    canVisit = false;
                    break;
                }
            }
            if (canVisit) {
                State next = current;
                next.node = edge.to;
                next.dist += edge.dist;
                next.learned[culture[edge.to]] = true;
                pq.push(next);
            }
        }
    }

    cout << -1 << endl;
    return 0;
}
