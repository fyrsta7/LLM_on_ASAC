#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>

using namespace std;

const int MOD = 10007;

vector<int> adj[1001];
int W[1001];
int dist[1001][1001];

void dfs(int u, int p, int root) {
    for (int v : adj[u]) {
        if (v == p) continue;
        dist[root][v] = dist[root][u] + 1;
        dfs(v, u, root);
    }
}

int main() {
    int n;
    cin >> n;

    for (int i = 1; i <= n; ++i) {
        cin >> W[i];
    }

    for (int i = 1; i < n; ++i) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    memset(dist, 0, sizeof(dist));

    for (int i = 1; i <= n; ++i) {
        dfs(i, -1, i);
    }

    int max_weight = 0;
    int sum_weight = 0;

    for (int i = 1; i <= n; ++i) {
        for (int j = i + 1; j <= n; ++j) {
            if (dist[i][j] == 2) {
                int weight = W[i] * W[j];
                max_weight = max(max_weight, weight);
                sum_weight = (sum_weight + weight) % MOD;
            }
        }
    }

    cout << max_weight << " " << sum_weight << endl;

    return 0;
}
