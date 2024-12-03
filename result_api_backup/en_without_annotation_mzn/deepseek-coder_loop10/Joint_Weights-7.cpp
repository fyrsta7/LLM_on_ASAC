#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <cstring>

using namespace std;

const int MOD = 10007;
const int INF = 1e9;

vector<int> W;
vector<vector<int>> adj;
vector<vector<int>> dist;

void bfs(int start, int n) {
    vector<int> d(n, INF);
    queue<int> q;
    q.push(start);
    d[start] = 0;
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        for (int v : adj[u]) {
            if (d[v] == INF) {
                d[v] = d[u] + 1;
                q.push(v);
            }
        }
    }
    dist[start] = d;
}

int main() {
    int n;
    cin >> n;

    W.resize(n);
    for (int i = 0; i < n; ++i) {
        cin >> W[i];
    }

    adj.resize(n);
    for (int i = 0; i < n - 1; ++i) {
        int u, v;
        cin >> u >> v;
        --u; --v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    dist.resize(n, vector<int>(n, INF));
    for (int i = 0; i < n; ++i) {
        bfs(i, n);
    }

    int max_weight = 0;
    int sum_weight = 0;

    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n; ++j) {
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
