#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <queue>

using namespace std;

struct Road {
    int dest, cost;
};

int main() {
    int n, m;
    cin >> n >> m;
    vector<int> price(n + 1);
    for (int i = 1; i <= n; ++i) cin >> price[i];

    vector<vector<Road>> graph(n + 1);
    for (int i = 0; i < m; ++i) {
        int u, v, t;
        cin >> u >> v >> t;
        graph[u].push_back({v, t});
        graph[v].push_back({u, t});
    }

    vector<int> dist(n + 1, INT_MAX);
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    pq.push({0, 1});
    dist[1] = 0;

    while (!pq.empty()) {
        int u = pq.top().second;
        int d = pq.top().first;
        pq.pop();

        if (d > dist[u]) continue;

        for (const auto& road : graph[u]) {
            int v = road.dest;
            int cost = road.cost;
            if (dist[u] + cost < dist[v]) {
                dist[v] = dist[u] + cost;
                pq.push({dist[v], v});
            }
        }
    }

    if (dist[n] == INT_MAX) {
        cout << "0\n";
        return 0;
    }

    vector<int> path;
    int current = n;
    while (current != 1) {
        path.push_back(current);
        for (const auto& road : graph[current]) {
            if (dist[road.dest] + road.cost == dist[current]) {
                current = road.dest;
                break;
            }
        }
    }
    path.push_back(1);
    reverse(path.begin(), path.end());

    int maxIncome = 0;
    for (int i = 0; i < path.size(); ++i) {
        for (int j = i + 1; j < path.size(); ++j) {
            maxIncome = max(maxIncome, price[path[j]] - price[path[i]]);
        }
    }

    cout << maxIncome << "\n";
    return 0;
}
