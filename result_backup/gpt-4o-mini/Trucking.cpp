#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

struct Edge {
    int to, weight;
};

int maxLoad(int start, int end, const vector<vector<Edge>>& graph) {
    priority_queue<pair<int, int>> pq;
    vector<int> maxWeight(graph.size(), -1);
    pq.push({INT_MAX, start});
    maxWeight[start] = INT_MAX;

    while (!pq.empty()) {
        int weight = pq.top().first;
        int node = pq.top().second;
        pq.pop();
        
        if (node == end) return weight;

        for (const Edge& edge : graph[node]) {
            int newWeight = min(weight, edge.weight);
            if (newWeight > maxWeight[edge.to]) {
                maxWeight[edge.to] = newWeight;
                pq.push({newWeight, edge.to});
            }
        }
    }
    return -1;
}

int main() {
    int n, m;
    cin >> n >> m;
    vector<vector<Edge>> graph(n + 1);

    for (int i = 0; i < m; i++) {
        int x, y, z;
        cin >> x >> y >> z;
        graph[x].push_back({y, z});
        graph[y].push_back({x, z});
    }

    int q;
    cin >> q;
    for (int i = 0; i < q; i++) {
        int x, y;
        cin >> x >> y;
        cout << maxLoad(x, y, graph) << endl;
    }

    return 0;
}