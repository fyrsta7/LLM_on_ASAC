#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

const int MAXN = 300005;
vector<int> adj[MAXN];
int n, T, size[MAXN], maxSubtree[MAXN];

void dfs(int u, int p) {
    size[u] = 1;
    maxSubtree[u] = 0;
    for (int v : adj[u]) {
        if (v == p) continue;
        dfs(v, u);
        size[u] += size[v];
        maxSubtree[u] = max(maxSubtree[u], size[v]);
    }
    maxSubtree[u] = max(maxSubtree[u], n - size[u]);
}

vector<int> findCenters(int root) {
    dfs(root, -1);
    int minMaxSubtree = n;
    vector<int> centers;
    for (int u = 1; u <= n; ++u) {
        if (maxSubtree[u] < minMaxSubtree) {
            minMaxSubtree = maxSubtree[u];
            centers.clear();
            centers.push_back(u);
        } else if (maxSubtree[u] == minMaxSubtree) {
            centers.push_back(u);
        }
    }
    return centers;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin >> T;
    while (T--) {
        cin >> n;
        for (int i = 1; i <= n; ++i) adj[i].clear();
        for (int i = 1; i < n; ++i) {
            int u, v;
            cin >> u >> v;
            adj[u].push_back(v);
            adj[v].push_back(u);
        }
        vector<int> centers = findCenters(1);
        long long sum = 0;
        for (int u = 1; u <= n; ++u) {
            for (int v : adj[u]) {
                if (u > v) continue;
                int root1 = u, root2 = v;
                if (size[root1] > size[root2]) swap(root1, root2);
                vector<int> centers1 = findCenters(root1);
                vector<int> centers2 = findCenters(root2);
                for (int c : centers1) sum += c;
                for (int c : centers2) sum += c;
            }
        }
        cout << sum << '\n';
    }
    return 0;
}
