#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <limits>

using namespace std;

const int INF = numeric_limits<int>::max();

vector<int> bfs(int start, const vector<vector<pair<int, int>>>& graph, int n) {
    vector<int> dist(n, INF);
    queue<int> q;
    q.push(start);
    dist[start] = 0;
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        for (const auto& [v, w] : graph[u]) {
            if (dist[v] == INF) {
                dist[v] = dist[u] + w;
                q.push(v);
            }
        }
    }
    return dist;
}

int main() {
    int n, s;
    cin >> n >> s;
    vector<vector<pair<int, int>>> graph(n);
    for (int i = 0; i < n - 1; ++i) {
        int u, v, w;
        cin >> u >> v >> w;
        graph[u - 1].emplace_back(v - 1, w);
        graph[v - 1].emplace_back(u - 1, w);
    }

    vector<int> dist1 = bfs(0, graph, n);
    int farthest1 = max_element(dist1.begin(), dist1.end()) - dist1.begin();
    vector<int> dist2 = bfs(farthest1, graph, n);
    int farthest2 = max_element(dist2.begin(), dist2.end()) - dist2.begin();
    vector<int> dist3 = bfs(farthest2, graph, n);

    int diameter = *max_element(dist3.begin(), dist3.end());
    int ans = INF;

    for (int i = 0; i < n; ++i) {
        int ecc = max(dist2[i], dist3[i]);
        if (ecc <= s) {
            ans = min(ans, ecc);
        }
    }

    cout << ans << endl;
    return 0;
}
