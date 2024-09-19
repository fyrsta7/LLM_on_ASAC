#include <iostream>
#include <vector>
#include <queue>
#include <map>
#include <set>
#include <algorithm>
#include <climits>

using namespace std;

struct Edge {
    int to, weight;
};

void bfs(int n, vector<vector<Edge>>& graph, const vector<int>& troops, vector<long long>& distances, int &maxDistance) {
    priority_queue<pair<long long, int>, vector<pair<long long, int>>, greater<pair<long long, int>>> pq;
    set<int> troopSet(troops.begin(), troops.end());
    
    for (int troop : troops) {
        pq.push({0, troop});
        distances[troop] = 0;
    }
    
    while (!pq.empty()) {
        auto [dist, city] = pq.top();
        pq.pop();
        
        if (dist > distances[city])
            continue;
        
        for (const Edge& edge : graph[city]) {
            int nextCity = edge.to;
            long long newDist = dist + edge.weight;
            
            if (troopSet.find(nextCity) == troopSet.end() && newDist < distances[nextCity]) {
                distances[nextCity] = newDist;
                pq.push({newDist, nextCity});
            }
        }
    }
    
    for (int i = 2; i <= n; ++i) {
        if (graph[i].size() == 1) { // leaf node
            maxDistance = max(maxDistance, distances[i]);
        }
    }
}

int main() {
    int n;
    cin >> n;
    
    vector<vector<Edge>> graph(n + 1);
    
    for (int i = 0; i < n - 1; ++i) {
        int u, v, w;
        cin >> u >> v >> w;
        graph[u].push_back({v, w});
        graph[v].push_back({u, w});
    }
    
    int m;
    cin >> m;
    vector<int> troops(m);
    
    for (int i = 0; i < m; ++i) {
        cin >> troops[i];
    }
    
    vector<long long> distances(n + 1, LLONG_MAX);
    int maxDistance = -1;
    
    bfs(n, graph, troops, distances, maxDistance);
    
    cout << maxDistance << endl;
    
    return 0;
}