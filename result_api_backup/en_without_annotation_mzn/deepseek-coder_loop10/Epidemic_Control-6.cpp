#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <limits>

using namespace std;

typedef pair<int, int> pii;

vector<vector<pii>> adj;
vector<int> army, camp, time_to_camp;
int n, m;

void dijkstra(int start, vector<int>& dist) {
    priority_queue<pii, vector<pii>, greater<pii>> pq;
    dist.assign(n + 1, numeric_limits<int>::max());
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
}

int main() {
    cin >> n;
    adj.resize(n + 1);
    for (int i = 1; i < n; ++i) {
        int u, v, w;
        cin >> u >> v >> w;
        adj[u].push_back({v, w});
        adj[v].push_back({u, w});
    }

    cin >> m;
    army.resize(m);
    camp.resize(m);
    time_to_camp.resize(m);
    for (int i = 0; i < m; ++i) {
        cin >> army[i];
    }
    for (int i = 0; i < m; ++i) {
        cin >> camp[i];
    }

    int max_time = 0;
    for (int i = 0; i < m; ++i) {
        vector<int> dist;
        dijkstra(army[i], dist);
        time_to_camp[i] = dist[camp[i]];
        max_time = max(max_time, time_to_camp[i]);
    }

    cout << max_time << endl;

    return 0;
}
