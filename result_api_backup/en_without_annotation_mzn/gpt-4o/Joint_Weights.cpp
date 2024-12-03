#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

const int MOD = 10007;

int n;
vector<pair<int, int>> roads;
vector<int> W;
vector<vector<int>> adj;
vector<vector<int>> dist;

void bfs(int start) {
    queue<int> q;
    vector<bool> visited(n + 1, false);
    q.push(start);
    visited[start] = true;
    dist[start][start] = 0;

    while (!q.empty) {
        int u = q.front();
        q.pop();

        for (int v : adj[u]) {
            if (!visited[v]) {
                visited[v] = true;
                dist[start][v] = dist[start][u] + 1;
                q.push(v);
            }
        }
    }
}

int main() {
    cin >> n;
    roads.resize(n - 1);
    W.resize(n + 1);
    adj.resize(n + 1);
    dist.assign(n + 1, vector<int>(n + 1, -1));

    for (int i = 0; i < n - 1; ++i) {
        cin >> roads[i].first >> roads[i].second;
        adj[roads[i].first].push_back(roads[i].second);
        adj[roads[i].second].push_back(roads[i].first);
    }

    for (int i = 1; i <= n; ++i) {
        cin >> W[i];
    }

    for (int i = 1; i <= n; ++i) {
        bfs(i);
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