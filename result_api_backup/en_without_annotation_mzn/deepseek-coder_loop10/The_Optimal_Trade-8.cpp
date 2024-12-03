#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <climits>

using namespace std;

struct Road {
    int dest, cost;
};

vector<int> dijkstra(int n, int m, const vector<vector<Road>>& adj, int start) {
    vector<int> dist(n + 1, INT_MAX);
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    dist[start] = 0;
    pq.push({0, start});

    while (!pq.empty()) {
        int u = pq.top().second;
        int d = pq.top().first;
        pq.pop();

        if (d > dist[u]) continue;

        for (const Road& road : adj[u]) {
            int v = road.dest;
            int cost = road.cost;
            if (dist[u] + cost < dist[v]) {
                dist[v] = dist[u] + cost;
                pq.push({dist[v], v});
            }
        }
    }

    return dist;
}

int main() {
    int n, m;
    cin >> n >> m;

    vector<int> price(n + 1);
    for (int i = 1; i <= n; ++i) {
        cin >> price[i];
    }

    vector<vector<Road>> adj(n + 1);
    for (int i = 0; i < m; ++i) {
        int u, v, t;
        cin >> u >> v >> t;
        adj[u].push_back({v, t == 1 ? 1 : 0});
        adj[v].push_back({u, t == 1 ? 1 : 0});
    }

    vector<int> distFromStart = dijkstra(n, m, adj, 1);
    vector<int> distToEnd = dijkstra(n, m, adj, n);

    int maxIncome = 0;
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) {
            if (distFromStart[i] != INT_MAX && distToEnd[j] != INT_MAX) {
                int income = price[j] - price[i];
                if (income > maxIncome) {
                    maxIncome = income;
                }
            }
        }
    }

    cout << max(0, maxIncome) << endl;

    return 0;
}