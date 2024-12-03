#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

const int MOD = 10007;

vector<int> weights;
vector<vector<int>> adj;
vector<int> maxWeights;
vector<int> sumWeights;

void dfs(int u, int parent) {
    int maxWeight = 0, sumWeight = 0;
    for (int v : adj[u]) {
        if (v == parent) continue;
        dfs(v, u);
        maxWeight = max(maxWeight, maxWeights[v]);
        sumWeight = (sumWeight + sumWeights[v]) % MOD;
    }
    maxWeights[u] = max(maxWeights[u], maxWeight);
    sumWeights[u] = (sumWeights[u] + sumWeight) % MOD;
    for (int v : adj[u]) {
        if (v == parent) continue;
        int jointWeight = (weights[u] * weights[v]) % MOD;
        maxWeights[u] = max(maxWeights[u], jointWeight);
        sumWeights[u] = (sumWeights[u] + jointWeight) % MOD;
    }
}

int main() {
    int n;
    cin >> n;
    weights.resize(n + 1);
    adj.resize(n + 1);
    maxWeights.resize(n + 1, 0);
    sumWeights.resize(n + 1, 0);

    for (int i = 1; i < n; ++i) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    for (int i = 1; i <= n; ++i) {
        cin >> weights[i];
    }

    dfs(1, 0);

    int maxJointWeight = 0, sumJointWeights = 0;
    for (int i = 1; i <= n; ++i) {
        maxJointWeight = max(maxJointWeight, maxWeights[i]);
        sumJointWeights = (sumJointWeights + sumWeights[i]) % MOD;
    }

    cout << maxJointWeight << " " << sumJointWeights << endl;

    return 0;
}
