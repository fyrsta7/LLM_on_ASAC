#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

const int MAXN = 2005;
vector<int> adj[MAXN];
int pos[MAXN], ans[MAXN], n;

void dfs(int u, int p) {
    for (int v : adj[u]) {
        if (v != p) {
            dfs(v, u);
        }
    }
    ans[u] = pos[u];
    for (int v : adj[u]) {
        if (v != p) {
            ans[u] = min(ans[u], ans[v]);
        }
    }
}

void solve() {
    cin >> n;
    for (int i = 1; i <= n; ++i) {
        adj[i].clear();
    }
    for (int i = 1; i <= n; ++i) {
        cin >> pos[i];
    }
    for (int i = 1; i < n; ++i) {
        int x, y;
        cin >> x >> y;
        adj[x].push_back(y);
        adj[y].push_back(x);
    }
    dfs(1, 0);
    for (int i = 1; i <= n; ++i) {
        cout << ans[i] << " ";
    }
    cout << endl;
}

int main() {
    int T;
    cin >> T;
    while (T--) {
        solve();
    }
    return 0;
}
