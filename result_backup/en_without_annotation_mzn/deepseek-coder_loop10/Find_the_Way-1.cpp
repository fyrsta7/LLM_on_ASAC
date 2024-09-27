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

bool bfs(int s, int t, int n) {
    queue<int> q;
    q.push(s);
    visited.assign(n + 1, false);
    visited[s] = true;
    parent.assign(n + 1, -1);

    while (!q.empty()) {
        int u = q.front();
        q.pop();

        for (const Edge& e : adj[u]) {
            int v = e.to;
            if (!visited[v]) {
                visited[v] = true;
                parent[v] = u;
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
    vector<pair<int, int>> roads(m);

    for (int i = 0; i < m; ++i) {
        int u, v;
        cin >> u >> v;
        roads[i] = {u, v};
        adj[u].push_back({v, i + 1});
    }

    if (!bfs(s, t, n)) {
        cout << "-1" << endl;
        return 0;
    }

    vector<int> path;
    for (int v = t; v != s; v = parent[v]) {
        path.push_back(v);
    }
    path.push_back(s);
    reverse(path.begin(), path.end());

    int len = path.size() - 1;
    bool cond2 = true;

    for (int i = 0; i < len; ++i) {
        int u = path[i], v = path[i + 1];
        for (const Edge& e : adj[u]) {
            if (e.to == v) continue;
            if (!bfs(e.to, t, n)) {
                cond2 = false;
                break;
            }
        }
        if (!cond2) break;
    }

    if (cond2) {
        cout << len - m << endl;
    } else {
        cout << len << endl;
    }

    return 0;
}