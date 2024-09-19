#include <iostream>
#include <vector>
#include <queue>
#include <tuple>
#include <limits>

using namespace std;

const int MAXN = 100005;
vector<pair<int, int>> graph[MAXN];
int dist[MAXN];
int n, m;

void dijkstra(int start) {
    fill(dist, dist + n + 1, numeric_limits<int>::max());
    dist[start] = 0;
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    pq.push({0, start});
    
    while (!pq.empty()) {
        auto [d, u] = pq.top();
        pq.pop();
        
        if (d > dist[u]) continue;
        
        for (auto [v, w] : graph[u]) {
            if (d + w < dist[v]) {
                dist[v] = d + w;
                pq.push({dist[v], v});
            }
        }
    }
}

int main() {
    cin >> n >> m;
    for (int i = 0; i < n - 1; ++i) {
        int a, b, t;
        cin >> a >> b >> t;
        graph[a].emplace_back(b, t);
        graph[b].emplace_back(a, t);
    }
    
    vector<pair<int, int>> plans(m);
    for (int i = 0; i < m; ++i) {
        cin >> plans[i].first >> plans[i].second;
    }
    
    long long total_time = 0;
    int max_distance = 0;

    for (const auto& plan : plans) {
        dijkstra(plan.first);
        total_time += dist[plan.second];
        max_distance = max(max_distance, dist[plan.second]);
    }

    cout << total_time - max_distance << endl;
    return 0;
}