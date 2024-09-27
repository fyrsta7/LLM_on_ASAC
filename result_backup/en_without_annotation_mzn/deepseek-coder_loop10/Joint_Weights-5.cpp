#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>

using namespace std;

const int MOD = 10007;

void dfs(int node, int parent, int depth, const vector<vector<int>>& adj, vector<int>& depths) {
    depths[node] = depth;
    for (int neighbor : adj[node]) {
        if (neighbor != parent) {
            dfs(neighbor, node, depth + 1, adj, depths);
        }
    }
}

int main() {
    int n;
    cin >> n;

    vector<vector<int>> adj(n + 1);
    for (int i = 0; i < n - 1; ++i) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    vector<int> W(n + 1);
    for (int i = 1; i <= n; ++i) {
        cin >> W[i];
    }

    vector<int> depths(n + 1, 0);
    dfs(1, -1, 0, adj, depths);

    int max_weight = 0;
    int sum_weight = 0;

    for (int i = 1; i <= n; ++i) {
        for (int j = i + 1; j <= n; ++j) {
            if (abs(depths[i] - depths[j]) == 2) {
                int product = W[i] * W[j];
                max_weight = max(max_weight, product);
                sum_weight = (sum_weight + product) % MOD;
            }
        }
    }

    cout << max_weight << " " << sum_weight << endl;

    return 0;
}
