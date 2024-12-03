#include <iostream>
#include <vector>
#include <queue>
#include <set>

using namespace std;

const int MAXN = 1000;
vector<int> adj[MAXN];
int parent[MAXN];
int depth[MAXN];
int subtree_size[MAXN];
int n;

void bfs(int root) {
    queue<int> q;
    q.push(root);
    parent[root] = -1;
    depth[root] = 0;
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        for (int v : adj[u]) {
            if (v != parent[u]) {
                parent[v] = u;
                depth[v] = depth[u] + 1;
                q.push(v);
            }
        }
    }
}

void dfs(int u) {
    subtree_size[u] = 1;
    for (int v : adj[u]) {
        if (v != parent[u]) {
            dfs(v);
            subtree_size[u] += subtree_size[v];
        }
    }
}

int find_center(int u) {
    int total_size = subtree_size[u];
    int p = parent[u];
    while (true) {
        bool is_center = true;
        for (int v : adj[u]) {
            if (v != p && subtree_size[v] > total_size / 2) {
                p = u;
                u = v;
                is_center = false;
                break;
            }
        }
        if (is_center) break;
    }
    return u;
}

int main() {
    cin >> n;
    for (int i = 0; i < n - 1; ++i) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    bfs(1);
    dfs(1);

    vector<vector<int>> centers(n - 1, vector<int>(2));
    for (int i = 0; i < n - 1; ++i) {
        int u = adj[i + 1][0];
        int v = adj[i + 1][1];
        centers[i][0] = find_center(u);
        centers[i][1] = find_center(v);
    }

    for (int i = 0; i < n - 1; ++i) {
        cout << centers[i][0] << " " << centers[i][1] << endl;
    }

    return 0;
}
