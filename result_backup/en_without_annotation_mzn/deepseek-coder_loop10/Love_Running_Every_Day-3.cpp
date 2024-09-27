#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

struct Edge {
    int to, id;
};

vector<int> dijkstra(int n, int m, const vector<vector<Edge>>& adj, int start, int end) {
    vector<int> dist(n, INT_MAX);
    vector<int> parent(n, -1);
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    dist[start] = 0;
    pq.push({0, start});

    while (!pq.empty()) {
        int u = pq.top().second;
        int d = pq.top().first;
        pq.pop();

        if (d > dist[u]) continue;

        for (const auto& e : adj[u]) {
            int v = e.to;
            int weight = 1;
            if (dist[u] + weight < dist[v]) {
                dist[v] = dist[u] + weight;
                parent[v] = u;
                pq.push({dist[v], v});
            }
        }
    }

    vector<int> path;
    for (int v = end; v != -1; v = parent[v]) {
        path.push_back(v);
    }
    reverse(path.begin(), path.end());
    return path;
}

int main() {
    int n, m;
    cin >> n >> m;

    vector<vector<Edge>> adj(n);
    vector<pair<int, int>> roads(n - 1);

    for (int i = 0; i < n - 1; ++i) {
        int u, v;
        cin >> u >> v;
        --u; --v;
        roads[i] = {u, v};
        adj[u].push_back({v, i});
        adj[v].push_back({u, i});
    }

    vector<int> watcher(n);
    for (int i = 0; i < n; ++i) {
        cin >> watcher[i];
    }

    vector<pair<int, int>> players(m);
    for (int i = 0; i < m; ++i) {
        int u, v;
        cin >> u >> v;
        --u; --v;
        players[i] = {u, v};
    }

    vector<vector<int>> routes(m);
    vector<int> times(m);
    vector<vector<int>> locations(m, vector<int>(n));

    for (int i = 0; i < m; ++i) {
        routes[i] = dijkstra(n, m, adj, players[i].first, players[i].second);
        times[i] = routes[i].size() - 1;
        for (int j = 0; j < times[i]; ++j) {
            locations[i][j] = routes[i][j];
        }
        locations[i][times[i]] = routes[i].back();
    }

    vector<int> watch_num(n, 0);
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            if (times[j] >= watcher[i] && locations[j][watcher[i]] == i) {
                watch_num[i]++;
            }
        }
    }

    for (int i = 0; i < n; ++i) {
        cout << watch_num[i] << " ";
    }
    cout << endl;

    return 0;
}
