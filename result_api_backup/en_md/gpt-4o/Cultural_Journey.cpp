#include <iostream>
#include <vector>
#include <queue>
#include <limits.h>
using namespace std;

struct Edge {
    int to, dist;
};

struct State {
    int country, culture, totalDist;
    bool operator>(const State& other) const {
        return totalDist > other.totalDist;
    }
};

int main() {
    int N, K, M, S, T;
    cin >> N >> K >> M >> S >> T;

    vector<int> countryToCulture(N + 1);
    for (int i = 1; i <= N; ++i) {
        cin >> countryToCulture[i];
    }

    vector<vector<int>> cultureRejection(K + 1, vector<int>(K + 1));
    for (int i = 1; i <= K; ++i) {
        for (int j = 1; j <= K; ++j) {
            cin >> cultureRejection[i][j];
        }
    }

    vector<vector<Edge>> graph(N + 1);
    for (int i = 0; i < M; ++i) {
        int u, v, d;
        cin >> u >> v >> d;
        graph[u].emplace_back(Edge{v, d});
        graph[v].emplace_back(Edge{u, d});
    }

    vector<vector<int>> minDist(N + 1, vector<int>(K + 1, INT_MAX));
    priority_queue<State, vector<State>, greater<State>> pq;

    int startCulture = countryToCulture[S];
    minDist[S][startCulture] = 0;
    pq.push({S, startCulture, 0});

    while (!pq.empty()) {
        State curr = pq.top();
        pq.pop();

        if (curr.totalDist > minDist[curr.country][curr.culture]) continue;

        for (const Edge& edge : graph[curr.country]) {
            int nextCountry = edge.to;
            int nextCulture = countryToCulture[nextCountry];
            int newDist = curr.totalDist + edge.dist;

            if (cultureRejection[curr.culture][nextCulture]) continue;

            if (newDist < minDist[nextCountry][nextCulture]) {
                minDist[nextCountry][nextCulture] = newDist;
                pq.push({nextCountry, nextCulture, newDist});
            }
        }
    }

    int result = INT_MAX;
    for (int c = 1; c <= K; ++c) {
        result = min(result, minDist[T][c]);
    }

    if (result == INT_MAX) {
        cout << -1 << endl;
    } else {
        cout << result << endl;
    }

    return 0;
}