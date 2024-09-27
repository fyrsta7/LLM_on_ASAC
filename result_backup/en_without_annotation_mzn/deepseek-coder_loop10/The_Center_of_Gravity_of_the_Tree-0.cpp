#include <iostream>
#include <vector>
#include <set>
#include <algorithm>

using namespace std;

struct Edge {
    int u, v;
};

vector<vector<int>> adj;
vector<Edge> edges;
vector<vector<set<int>>> subtree;
vector<vector<vector<set<int>>>> subsubtree;
vector<vector<int>> center;

bool dfs(int u, int p, int target, set<int>& path, const set<int>& avoid) {
    path.insert(u);
    if (u == target) return true;
    for (int v : adj[u]) {
        if (v == p) continue;
        if (avoid.count(v)) continue;
        if (dfs(v, u, target, path, avoid)) return true;
    }
    path.erase(u);
    return false;
}

bool connect_without(int a, int b, const set<int>& avoid) {
    set<int> path;
    return dfs(a, -1, b, path, avoid);
}

int main() {
    int n;
    cin >> n;

    adj.resize(n + 1);
    edges.resize(n - 1);
    subtree.resize(n - 1, vector<set<int>>(2));
    subsubtree.resize(n - 1, vector<vector<set<int>>>(2, vector<set<int>>(n)));
    center.resize(n - 1, vector<int>(2));

    for (int i = 0; i < n - 1; ++i) {
        int u, v;
        cin >> u >> v;
        edges[i] = {u, v};
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    for (int i = 0; i < n - 1; ++i) {
        int u = edges[i].u, v = edges[i].v;
        subtree[i][0].insert(u);
        subtree[i][1].insert(v);

        for (int j = 0; j < 2; ++j) {
            for (int k : subtree[i][j]) {
                for (int l : subtree[i][j]) {
                    if (k != l && !connect_without(k, l, {i})) {
                        cout << "No solution" << endl;
                        return 0;
                    }
                }
            }
        }
    }

    for (int i = 0; i < n - 1; ++i) {
        for (int j = 0; j < 2; ++j) {
            for (int k = 1; k <= n; ++k) {
                for (int x : subtree[i][j]) {
                    for (int y : subtree[i][j]) {
                        if (x != y && !connect_without(x, y, {t for t in 1..n-1 if edge[t].u != center[i][j] && edge[t].v != center[i][j]} union {i})) {
                            cout << "No solution" << endl;
                            return 0;
                        }
                    }
                }
                if (subsubtree[i][j][k].size() > n / 2) {
                    cout << "No solution" << endl;
                    return 0;
                }
            }
            int count = 0;
            for (int k = 1; k <= n; ++k) {
                if (!subsubtree[i][j][k].empty()) ++count;
            }
            int expected = 0;
            for (int l = 0; l < n - 1; ++l) {
                if (l != i && (edges[l].u == center[i][j] || edges[l].v == center[i][j])) ++expected;
            }
            if (count != expected) {
                cout << "No solution" << endl;
                return 0;
            }
        }
    }

    for (int i = 0; i < n - 1; ++i) {
        for (int j = 0; j < 2; ++j) {
            if (!subtree[i][j].count(center[i][j])) {
                cout << "No solution" << endl;
                return 0;
            }
        }
    }

    for (int i = 0; i < n - 1; ++i) {
        cout << center[i][0] << " " << center[i][1] << endl;
    }

    return 0;
}
