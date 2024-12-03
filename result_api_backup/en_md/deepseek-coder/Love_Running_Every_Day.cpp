#include <vector>
#include <iostream>
using namespace std;

const int MAXN = 1e5 + 5;
vector<int> adj[MAXN];
int w[MAXN], ans[MAXN];
vector<pair<int, int>> queries[MAXN];

void dfs(int u, int p, vector<int>& times) {
    for (auto& q : queries[u]) {
        ans[u] += upper_bound(times.begin(), times.end(), q.second) - lower_bound(times.begin(), times.end(), q.first);
    }
    for (int v : adj[u]) {
        if (v == p) continue;
        times.push_back(times.back() + 1);
        dfs(v, u, times);
        times.pop_back();
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int n, m;
    cin >> n >> m;
    for (int i = 1; i < n; ++i) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    for (int i = 1; i <= n; ++i) {
        cin >> w[i];
    }
    for (int i = 0; i < m; ++i) {
        int s, t;
        cin >> s >> t;
        queries[t].emplace_back(s, w[t]);
    }

    vector<int> times;
    times.push_back(0);
    dfs(1, 0, times);

    for (int i = 1; i <= n; ++i) {
        cout << ans[i] << " ";
    }
    return 0;
}
