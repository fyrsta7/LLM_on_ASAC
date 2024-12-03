#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <climits>

using namespace std;

typedef pair<int, int> pii;

vector<int> dijkstra(int n, const vector<vector<pii>>& adj, int start) {
    vector<int> dist(n + 1, INT_MAX);
    priority_queue<pii, vector<pii>, greater<pii>> pq;
    dist[start] = 0;
    pq.push({0, start});

    while (!pq.empty()) {
        int u = pq.top().second;
        int d = pq.top().first;
        pq.pop();

        if (d > dist[u]) continue;

        for (auto& edge : adj[u]) {
            int v = edge.first;
            int weight = edge.second;

            if (dist[u] + weight < dist[v]) {
                dist[v] = dist[u] + weight;
                pq.push({dist[v], v});
            }
        }
    }

    return dist;
}

int main() {
    int n;
    cin >> n;
    vector<int> u(n - 1), v(n - 1), w(n - 1);
    for (int i = 0; i < n - 1; ++i) {
        cin >> u[i] >> v[i] >> w[i];
    }

    int m;
    cin >> m;
    vector<int> army(m);
    for (int i = 0; i < m; ++i) {
        cin >> army[i];
    }

    vector<vector<pii>> adj(n + 1);
    for (int i = 0; i < n - 1; ++i) {
        adj[u[i]].push_back({v[i], w[i]});
        adj[v[i]].push_back({u[i], w[i]});
    }

    vector<int> dist_from_1 = dijkstra(n, adj, 1);
    vector<int> max_time(n + 1, 0);

    for (int i = 2; i <= n; ++i) {
        if (adj[i].size() == 1) {
            max_time[i] = dist_from_1[i];
        }
    }

    for (int i = 0; i < m; ++i) {
        vector<int> dist_from_army = dijkstra(n, adj, army[i]);
        for (int j = 2; j <= n; ++j) {
            if (adj[j].size() == 1) {
                max_time[j] = min(max_time[j], dist_from_army[j]);
            }
        }
    }

    int result = *max_element(max_time.begin() + 2, max_time.end());
    cout << result << endl;

    return 0;
}
