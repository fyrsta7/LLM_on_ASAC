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
        for (auto& edge : graph[u]) {
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

int find_diameter(const vector<vector<pair<int, int>>>& graph, int n) {
    vector<int> dist1 = bfs(0, graph, n);
    int farthest = max_element(dist1.begin(), dist1.end()) - dist1.begin();
    vector<int> dist2 = bfs(farthest, graph, n);
    return *max_element(dist2.begin(), dist2.end());
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

    int diameter = find_diameter(graph, n);
    vector<int> dist = bfs(0, graph, n);
    int farthest = max_element(dist.begin(), dist.end()) - dist.begin();
    vector<int> dist_from_farthest = bfs(farthest, graph, n);

    int ans = INF;
    for (int i = 0; i < n; ++i) {
        int max_dist = 0;
        for (int j = 0; j < n; ++j) {
            max_dist = max(max_dist, min(dist[j], dist_from_farthest[j]));
        }
        ans = min(ans, max_dist);
    }

    cout << ans << endl;
    return 0;
}
