#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const int MAXN = 100005;
const int INF = 1e9;

int n, m;
int cost[MAXN];
vector<int> adj[MAXN];
int dp[MAXN][2]; // dp[u][0] means min cost if u doesn't have army, dp[u][1] means min cost if u has army

void dfs(int u, int parent) {
    dp[u][0] = 0;
    dp[u][1] = cost[u];
    int sumZero = 0;
    int minDiff = INF;

    for (int v : adj[u]) {
        if (v == parent) continue;
        dfs(v, u);
        
        dp[u][0] += dp[v][1];
        dp[u][1] += min(dp[v][0], dp[v][1]);

        sumZero += dp[v][1];
        minDiff = min(minDiff, dp[v][1] - min(dp[v][0], dp[v][1]));
    }

    if (adj[u].size() > 1) {
        dp[u][0] = min(dp[u][0], sumZero - minDiff);
    }
}

int solve(int a, int x, int b, int y) {
    vector<pair<int, int>> restrictions = {{a, x}, {b, y}};
    for (const auto& [u, state] : restrictions) {
        if (state == 0) {
            if (dp[u][1] == INF) {
                return -1;
            }
        }
    }
    
    int totalCost = 0;
    for (const auto& [u, state] : restrictions) {
        if (state == 1) {
            totalCost += dp[u][1];
        } else {
            totalCost += dp[u][0];
        }
    }
    
    return totalCost;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string type;
    cin >> n >> m >> type;
    
    for (int i = 1; i <= n; i++) {
        cin >> cost[i];
    }
    
    for (int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    
    dfs(1, -1);
    
    while (m--) {
        int a, x, b, y;
        cin >> a >> x >> b >> y;
        if (adj[a].size() > 1 && x == 0 && adj[b].size() > 1 && y == 0) {
            cout << -1 << endl;
        } else {
            cout << solve(a, x, b, y) << endl;
        }
    }

    return 0;
}