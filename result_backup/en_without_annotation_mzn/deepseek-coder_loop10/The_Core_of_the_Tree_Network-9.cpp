#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <climits>

using namespace std;

vector<int> bfs(int start, int n, const vector<vector<pair<int, int>>>& adj) {
    vector<int> dist(n, INT_MAX);
    queue<int> q;
    q.push(start);
    dist[start] = 0;
    
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        for (auto& edge : adj[u]) {
            int v = edge.first;
            int w = edge.second;
            if (dist[v] == INT_MAX) {
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
    vector<vector<pair<int, int>>> adj(n);
    for (int i = 0; i < n - 1; ++i) {
        int u, v, w;
        cin >> u >> v >> w;
        adj[u - 1].emplace_back(v - 1, w);
        adj[v - 1].emplace_back(u - 1, w);
    }

    vector<int> dist1 = bfs(0, n, adj);
    int farthest1 = max_element(dist1.begin(), dist1.end()) - dist1.begin();
    vector<int> dist2 = bfs(farthest1, n, adj);
    int farthest2 = max_element(dist2.begin(), dist2.end()) - dist2.begin();
    vector<int> dist3 = bfs(farthest2, n, adj);

    int diameter = *max_element(dist3.begin(), dist3.end());
    int ans = INT_MAX;

    for (int i = 0; i < n; ++i) {
        int max_dist = max(dist2[i], dist3[i]);
        if (max_dist <= s) {
            ans = min(ans, max_dist);
        }
    }

    cout << ans << endl;
    return 0;
}