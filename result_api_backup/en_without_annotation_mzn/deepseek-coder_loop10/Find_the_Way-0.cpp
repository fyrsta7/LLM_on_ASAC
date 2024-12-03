#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

struct Edge {
    int to, id;
};

vector<vector<Edge>> adj;
vector<int> parent;
vector<bool> visited;
vector<int> route;

bool bfs(int s, int t, int n) {
    queue<int> q;
    q.push(s);
    visited.assign(n + 1, false);
    parent.assign(n + 1, -1);
    visited[s] = true;

    while (!q.empty()) {
        int u = q.front();
        q.pop();

        for (const Edge &e : adj[u]) {
            int v = e.to;
            if (!visited[v]) {
                visited[v] = true;
                parent[v] = u;
                route[v] = e.id;
                q.push(v);
            }
        }
    }

    return visited[t];
}

int main() {
    int n, m, s, t;
    cin >> n >> m >> s >> t;

    adj.resize(n + 1);
    route.resize(n + 1);
    vector<pair<int, int>> roads(m + 1);

    for (int i = 1; i <= m; ++i) {
        int u, v;
        cin >> u >> v;
        roads[i] = {u, v};
        adj[u].push_back({v, i});
    }

    if (!bfs(s, t, n)) {
        cout << "-1" << endl;
        return 0;
    }

    vector<int> path;
    for (int v = t; v != s; v = parent[v]) {
        path.push_back(route[v]);
    }
    reverse(path.begin(), path.end());

    int len = path.size();
    bool cond2 = true;

    for (int i = 0; i < len; ++i) {
        int u = roads[path[i]].first;
        int v = roads[path[i]].second;
        bool found = false;
        for (const Edge &e : adj[u]) {
            if (e.to == t) {
                found = true;
                break;
            }
        }
        for (const Edge &e : adj[v]) {
            if (e.to == t) {
                found = true;
                break;
            }
        }
        if (!found) {
            cond2 = false;
            break;
        }
    }

    if (cond2) {
        cout << len << endl;
    } else {
        cout << "-1" << endl;
    }

    return 0;
}