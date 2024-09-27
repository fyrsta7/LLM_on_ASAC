#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

const int MAXN = 1000;
vector<int> adj[MAXN];
int parent[MAXN];
int depth[MAXN];
int subtree_size[MAXN];
int n;

void dfs(int v, int p, int d) {
    parent[v] = p;
    depth[v] = d;
    subtree_size[v] = 1;
    for (int u : adj[v]) {
        if (u != p) {
            dfs(u, v, d + 1);
            subtree_size[v] += subtree_size[u];
        }
    }
}

int find_centroid(int v, int p) {
    for (int u : adj[v]) {
        if (u != p && subtree_size[u] > n / 2) {
            return find_centroid(u, v);
        }
    }
    return v;
}

int main() {
    cin >> n;
    for (int i = 0; i < n - 1; ++i) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    dfs(1, -1, 0);

    vector<pair<int, int>> centers;
    for (int i = 1; i <= n; ++i) {
        int centroid = find_centroid(i, parent[i]);
        centers.push_back({centroid, i});
    }

    sort(centers.begin(), centers.end());
    centers.erase(unique(centers.begin(), centers.end()), centers.end());

    for (auto& center : centers) {
        cout << center.first << " " << center.second << endl;
    }

    return 0;
}
