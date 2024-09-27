#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <limits>

using namespace std;

const int INF = numeric_limits<int>::max();

struct Edge {
    int to, weight;
};

vector<int> bfs(int start, const vector<vector<Edge>>& graph, int n) {
    vector<int> dist(n, INF);
    queue<int> q;
    q.push(start);
    dist[start] = 0;
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        for (const Edge& e : graph[u]) {
            if (dist[e.to] == INF) {
                dist[e.to] = dist[u] + e.weight;
                q.push(e.to);
            }
        }
    }
    return dist;
}

int find_diameter(const vector<vector<Edge>>& graph, int n) {
    vector<int> dist1 = bfs(0, graph, n);
    int farthest = max_element(dist1.begin(), dist1.end()) - dist1.begin();
    vector<int> dist2 = bfs(farthest, graph, n);
    return *max_element(dist2.begin(), dist2.end());
}

int main() {
    int n, s;
    cin >> n >> s;
    vector<vector<Edge>> graph(n);
    for (int i = 0; i < n - 1; ++i) {
        int u, v, w;
        cin >> u >> v >> w;
        graph[u - 1].push_back({v - 1, w});
        graph[v - 1].push_back({u - 1, w});
    }

    int diameter = find_diameter(graph, n);
    int ans = INF;

    for (int i = 0; i < n; ++i) {
        vector<int> dist = bfs(i, graph, n);
        int max_dist = *max_element(dist.begin(), dist.end());
        if (max_dist <= s) {
            ans = min(ans, max_dist);
        }
    }

    cout << ans << endl;
    return 0;
}
