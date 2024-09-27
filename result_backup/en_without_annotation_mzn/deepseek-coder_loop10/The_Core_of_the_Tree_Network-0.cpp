#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <limits>

using namespace std;

const int INF = numeric_limits<int>::max();

vector<int> bfs(int start, const vector<vector<pair<int, int>>>& adj, int n) {
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

    // Find the diameter of the tree
    vector<int> dist1 = bfs(0, adj, n);
    int farthest = max_element(dist1.begin(), dist1.end()) - dist1.begin();
    vector<int> dist2 = bfs(farthest, adj, n);
    int diameter = *max_element(dist2.begin(), dist2.end());

    // Find the diameter path
    int end_point = max_element(dist2.begin(), dist2.end()) - dist2.begin();
    vector<int> path;
    int current = end_point;
    while (current != farthest) {
        path.push_back(current);
        for (auto& edge : adj[current]) {
            if (dist2[edge.first] == dist2[current] - edge.second) {
                current = edge.first;
                break;
            }
        }
    }
    path.push_back(farthest);
    reverse(path.begin(), path.end());

    // Find the core path
    int core_begin = 0, core_end = path.size() - 1;
    int core_length = 0;
    for (int i = 0; i < path.size() - 1; ++i) {
        core_length += dist2[path[i]] - dist2[path[i + 1]];
        if (core_length > s) {
            core_end = i;
            break;
        }
    }

    // Calculate ECC
    int ans = 0;
    for (int i = core_begin; i <= core_end; ++i) {
        vector<int> dist = bfs(path[i], adj, n);
        ans = max(ans, *max_element(dist.begin(), dist.end()));
    }

    cout << ans << endl;
    return 0;
}
