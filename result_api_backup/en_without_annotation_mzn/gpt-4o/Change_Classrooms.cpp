#include <iostream>
#include <vector>
#include <queue>
#include <limits>
#include <cmath>
using namespace std;

struct Edge {
    int to, length;
};

struct Node {
    int vertex, distance;
    bool operator>(const Node& other) const {
        return distance > other.distance;
    }
};

int dijkstra(int v, const vector<vector<Edge>>& graph, int start, int end) {
    vector<int> distances(v + 1, numeric_limits<int>::max());
    vector<bool> visited(v + 1, false);
    priority_queue<Node, vector<Node>, greater<Node>> pq;
    
    distances[start] = 0;
    pq.push({start, 0});
    
    while (!pq.empty()) {
        Node node = pq.top();
        pq.pop();
        
        if (visited[node.vertex]) continue;
        visited[node.vertex] = true;
        
        for (const Edge& edge : graph[node.vertex]) {
            int next_vertex = edge.to;
            int new_dist = distances[node.vertex] + edge.length;
            if (new_dist < distances[next_vertex]) {
                distances[next_vertex] = new_dist;
                pq.push({next_vertex, new_dist});
            }
        }
    }
    
    return distances[end];
}

int main() {
    int n, m, v, e;
    cin >> n >> m >> v >> e;
    
    vector<int> C(n), D(n);
    vector<float> K(n);
    vector<vector<Edge>> graph(v + 1);
    
    for (int i = 0; i < n; ++i) cin >> C[i];
    for (int i = 0; i < n; ++i) cin >> D[i];
    for (int i = 0; i < n; ++i) cin >> K[i];
    
    for (int i = 0; i < e; ++i) {
        int A, B, W;
        cin >> A >> B >> W;
        graph[A].push_back({B, W});
        graph[B].push_back({A, W});
    }
    
    vector<int> changes(n, 0);
    for (int i = 0; i < m; ++i) {
        int change;
        cin >> change;
        changes[change - 1] = 1;
    }
    
    float obj = 0;
    for (int i = 0; i < n - 1; ++i) {
        int pcc = dijkstra(v, graph, C[i], C[i+1]);
        int pdc = dijkstra(v, graph, D[i], C[i+1]);
        int pcd = dijkstra(v, graph, C[i], D[i+1]);
        int pdd = dijkstra(v, graph, D[i], D[i+1]);
        
        if (changes[i] && changes[i+1]) {
            obj += pcc * (1 - K[i]) * (1 - K[i+1]) + pdc * K[i] * (1 - K[i+1]) +
                   pcd * K[i+1] * (1 - K[i]) + pdd * K[i] * K[i+1];
        }
        else if (!changes[i] && changes[i+1]) {
            obj += pcc * (1 - K[i+1]) + pcd * K[i+1];
        }
        else if (changes[i] && !changes[i+1]) {
            obj += pcc * (1 - K[i]) + pdc * K[i];
        }
        else {
            obj += pcc;
        }
    }
    
    cout << round(obj * 100) / 100 << endl;
    return 0;
}
