#include <iostream>
#include <vector>
#include <set>
#include <algorithm>

using namespace std;

const int MAXN = 1000;

int n;
vector<int> adj[MAXN];
int parent[MAXN];
int subtree_size[MAXN];

void dfs(int v, int p) {
    parent[v] = p;
    subtree_size[v] = 1;
    for (int u : adj[v]) {
        if (u != p) {
            dfs(u, v);
            subtree_size[v] += subtree_size[u];
        }
    }
}

int find_centroid(int v) {
    int total_size = subtree_size[v];
    bool found;
    do {
        found = false;
        for (int u : adj[v]) {
            if (u != parent[v] && subtree_size[u] > total_size / 2) {
                v = u;
                found = true;
                break;
            }
        }
    } while (found);
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

    dfs(1, -1);

    vector<vector<int>> centers(n - 1, vector<int>(2));
    for (int i = 0; i < n - 1; ++i) {
        int u = adj[i + 1][0];
        int v = adj[i + 1][1];
        centers[i][0] = find_centroid(u);
        centers[i][1] = find_centroid(v);
    }

    for (int i = 0; i < n - 1; ++i) {
        cout << centers[i][0] << " " << centers[i][1] << endl;
    }

    return 0;
}
