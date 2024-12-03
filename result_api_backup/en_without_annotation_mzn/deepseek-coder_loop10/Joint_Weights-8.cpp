#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <cstring>

using namespace std;

const int MOD = 10007;

vector<int> bfs(int start, int n, const vector<vector<int>>& adj) {
    vector<int> dist(n, -1);
    queue<int> q;
    q.push(start);
    dist[start] = 0;
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        for (int v : adj[u]) {
            if (dist[v] == -1) {
                dist[v] = dist[u] + 1;
                q.push(v);
            }
        }
    }
    return dist;
}

int main() {
    int n;
    cin >> n;
    vector<vector<int>> roads(n - 1, vector<int>(2));
    vector<int> W(n);
    for (int i = 0; i < n - 1; ++i) {
        cin >> roads[i][0] >> roads[i][1];
        roads[i][0]--;
        roads[i][1]--;
    }
    for (int i = 0; i < n; ++i) {
        cin >> W[i];
    }

    vector<vector<int>> adj(n);
    for (const auto& road : roads) {
        adj[road[0]].push_back(road[1]);
        adj[road[1]].push_back(road[0]);
    }

    vector<vector<int>> dist(n);
    for (int i = 0; i < n; ++i) {
        dist[i] = bfs(i, n, adj);
    }

    int max_weight = 0;
    int sum_weight = 0;
    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n; ++j) {
            if (dist[i][j] == 2) {
                int product = W[i] * W[j];
                max_weight = max(max_weight, product);
                sum_weight = (sum_weight + product) % MOD;
            }
        }
    }

    cout << max_weight << " " << sum_weight << endl;
    return 0;
}
