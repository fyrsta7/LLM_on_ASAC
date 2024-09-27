#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <limits>

using namespace std;

const int INF = numeric_limits<int>::max();

vector<int> bfs(int start, int n, const vector<vector<pair<int, int>>>& adj) {
    vector<int> dist(n, INF);
    queue<int> q;
    q.push(start);
    dist[start] = 0;
    
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        for (auto& edge : adj[u]) {
            int v = edge.first;
            int w = edge.second;
            if (dist[v] == INF) {
                dist[v] = dist[u] + w;
                q.push(v);
            }
        }
    }
    return dist;
}

int find_diameter(int n, const vector<vector<pair<int, int>>>& adj) {
    vector<int> dist1 = bfs(0, n, adj);
    int farthest = max_element(dist1.begin(), dist1.end()) - dist1.begin();
    vector<int> dist2 = bfs(farthest, n, adj);
    return *max_element(dist2.begin(), dist2.end());
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

    int diameter = find_diameter(n, adj);
    int ans = INF;

    for (int i = 0; i < n; ++i) {
        vector<int> dist = bfs(i, n, adj);
        int max_dist = *max_element(dist.begin(), dist.end());
        if (max_dist <= s) {
            ans = min(ans, max_dist);
        }
    }

    cout << ans << endl;
    return 0;
}