#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

struct Edge {
    int to, weight;
};

void bfs(int start, vector<vector<Edge>>& graph, vector<int>& distances) {
    int n = graph.size();
    distances.assign(n, -1);
    queue<int> q;
    q.push(start);
    distances[start] = 0;
    
    while (!q.empty()) {
        int node = q.front();
        q.pop();
        
        for (auto& edge : graph[node]) {
            if (distances[edge.to] == -1) {
                distances[edge.to] = distances[node] + edge.weight;
                q.push(edge.to);
            }
        }
    }
}

pair<int, int> findFarthestNode(vector<vector<Edge>>& graph, int start) {
    vector<int> distances;
    bfs(start, graph, distances);
    int farthestNode = -1, maxDistance = -1;

    for (int i = 0; i < distances.size(); i++) {
        if (distances[i] > maxDistance) {
            maxDistance = distances[i];
            farthestNode = i;
        }
    }
    
    return {farthestNode, maxDistance};
}

int main() {
    int n, s;
    cin >> n >> s;
    
    vector<vector<Edge>> graph(n + 1);
    for (int i = 0; i < n - 1; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        graph[u].push_back({v, w});
        graph[v].push_back({u, w});
    }
    
    // Find one endpoint of the diameter
    int farthestFromStart = findFarthestNode(graph, 1).first;
    // Find the other endpoint of the diameter
    int farthestFromEnd = findFarthestNode(graph, farthestFromStart).first;

    // Get distances from both endpoints
    vector<int> distFromStart, distFromEnd;
    bfs(farthestFromStart, graph, distFromStart);
    bfs(farthestFromEnd, graph, distFromEnd);
    
    // Calculate the minimum eccentricity with length constraint
    int minEccentricity = INT_MAX;

    for (int i = 1; i <= n; i++) {
        int pathLengthLimit = s;
        
        for (int j = 1; j <= n; j++) {
            if (distFromStart[i] + distFromEnd[i] <= pathLengthLimit) {
                int eccentricity = max(distFromStart[j], distFromEnd[j]);
                minEccentricity = min(minEccentricity, eccentricity);
            }
        }
    }

    cout << minEccentricity << endl;
    return 0;
}