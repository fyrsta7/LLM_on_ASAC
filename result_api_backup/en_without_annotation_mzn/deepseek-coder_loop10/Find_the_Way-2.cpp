#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

struct Edge {
    int to, id;
};

int main() {
    int n, m, s, t;
    cin >> n >> m >> s >> t;
    s--; t--;

    vector<vector<Edge>> adj(n);
    vector<pair<int, int>> roads(m);
    for (int i = 0; i < m; ++i) {
        int u, v;
        cin >> u >> v;
        u--; v--;
        adj[u].push_back({v, i});
        roads[i] = {u, v};
    }

    vector<vector<bool>> available(n, vector<bool>(n, false));
    for (int i = 0; i < n; ++i) available[i][i] = true;
    for (int i = 0; i < m; ++i) available[roads[i].first][roads[i].second] = true;

    for (int k = 0; k < n; ++k) {
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                if (available[i][k] && available[k][j]) {
                    available[i][j] = true;
                }
            }
        }
    }

    if (!available[s][t]) {
        cout << "-1" << endl;
        return 0;
    }

    vector<int> dist(n, -1);
    vector<int> parent(n, -1);
    queue<int> q;
    q.push(s);
    dist[s] = 0;

    while (!q.empty()) {
        int u = q.front();
        q.pop();
        for (const Edge &e : adj[u]) {
            if (dist[e.to] == -1) {
                dist[e.to] = dist[u] + 1;
                parent[e.to] = e.id;
                q.push(e.to);
            }
        }
    }

    if (dist[t] == -1) {
        cout << "-1" << endl;
        return 0;
    }

    vector<int> route;
    for (int v = t; v != s; v = roads[parent[v]].first) {
        route.push_back(parent[v]);
    }
    reverse(route.begin(), route.end());

    bool cond2 = true;
    for (int i = 0; i < route.size(); ++i) {
        int u = roads[route[i]].first;
        int v = roads[route[i]].second;
        for (const Edge &e : adj[u]) {
            if (!available[e.to][t] && !available[t][e.to]) {
                cond2 = false;
                break;
            }
        }
        if (!cond2) break;
        for (const Edge &e : adj[v]) {
            if (!available[e.to][t] && !available[t][e.to]) {
                cond2 = false;
                break;
            }
        }
        if (!cond2) break;
    }

    int score = cond2 ? route.size() - m : route.size();
    cout << score << endl;

    return 0;
}
