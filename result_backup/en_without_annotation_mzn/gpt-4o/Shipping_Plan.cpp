#include <iostream>
#include <vector>
#include <queue>
#include <climits>
using namespace std;

struct Edge {
    int to, cost;
};

vector<vector<Edge>> adj;

int dijkstra(int n, int start, int end) {
    vector<int> dist(n, INT_MAX);
    dist[start] = 0;
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    pq.push({0, start});
    
    while(!pq.empty()) {
        int u = pq.top().second;
        int d = pq.top().first;
        pq.pop();

        if (d > dist[u]) continue;
        
        for (auto &edge : adj[u]) {
            int v = edge.to, cost = edge.cost;
            if (dist[u] + cost < dist[v]) {
                dist[v] = dist[u] + cost;
                pq.push({dist[v], v});
            }
        }
    }

    return dist[end];
}

int main() {
    int n, m;
    cin >> n >> m;
    
    adj.resize(n);
    
    for (int i = 0; i < n - 1; ++i) {
        int u, v, c;
        cin >> u >> v >> c;
        adj[u-1].emplace_back(Edge{v-1, c});
        adj[v-1].emplace_back(Edge{u-1, c});
    }

    vector<pair<int, int>> plans(m);
    for (int i = 0; i < m; ++i) {
        cin >> plans[i].first >> plans[i].second;
        plans[i].first--;
        plans[i].second--;
    }
    
    int max_time = 0;
    for (int i = 0; i < m; ++i) {
        max_time = max(max_time, dijkstra(n, plans[i].first, plans[i].second));
    }
    
    cout << max_time << endl;
    return 0;
}