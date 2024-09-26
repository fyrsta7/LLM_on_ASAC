#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

const int MAXN = 50005;
const int INF = 1e9;

struct Edge {
    int to, len;
};

vector<Edge> adj[MAXN];
int n, m;

int dfs(int u, int p, int limit, vector<int>& paths) {
    int max_path = 0;
    vector<int> children_paths;
    for (auto& e : adj[u]) {
        if (e.to == p) continue;
        int child_path = dfs(e.to, u, limit, paths) + e.len;
        if (child_path >= limit) {
            paths.push_back(child_path);
        } else {
            children_paths.push_back(child_path);
        }
    }
    sort(children_paths.rbegin(), children_paths.rend());
    for (int i = 0; i < min(2, (int)children_paths.size()); ++i) {
        max_path += children_paths[i];
    }
    return max_path;
}

bool check(int limit) {
    vector<int> paths;
    dfs(1, -1, limit, paths);
    sort(paths.rbegin(), paths.rend());
    int cnt = 0;
    for (int i = 0; i < min(m, (int)paths.size()); ++i) {
        if (paths[i] >= limit) cnt++;
    }
    return cnt >= m;
}

int main() {
    cin >> n >> m;
    for (int i = 1; i < n; ++i) {
        int a, b, l;
        cin >> a >> b >> l;
        adj[a].push_back({b, l});
        adj[b].push_back({a, l});
    }

    int l = 0, r = INF;
    while (l < r) {
        int mid = (l + r + 1) / 2;
        if (check(mid)) {
            l = mid;
        } else {
            r = mid - 1;
        }
    }
    cout << l << endl;
    return 0;
}
