#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
using namespace std;

struct Graph {
    unordered_map<int, vector<int>> adj;
    
    void addEdge(int u, int v) {
        adj[u].push_back(v);
    }

    bool bfs(int n, vector<int>& parent) {
        vector<int> visited(n + 1, 0);
        queue<int> q;
        q.push(1);
        visited[1] = true;
        
        while (!q.empty()) {
            int node = q.front();
            q.pop();
            
            for (int neighbour : adj[node]) {
                if (!visited[neighbour]) {
                    visited[neighbour] = true;
                    parent[neighbour] = node;
                    q.push(neighbour);
                    if (neighbour == n)
                        return true;
                }
            }
        }
        return false;
    }
    
    int findMinCost(int n) {
        vector<int> parent(n + 1, -1);

        // Check if path exists from 1 to n
        if (!bfs(n, parent)) {
            return -1;
        }

        // Trace the path from n to 1
        vector<int> path;
        for (int at = n; at != -1; at = parent[at]) {
            path.push_back(at);
        }
        reverse(path.begin(), path.end());

        return path.size() - 1;  // Number of edges in the path
    }
};

int main() {
    int n;
    cin >> n;

    Graph graph;

    for (int i = 1; i <= n; ++i) {
        int a, b;
        cin >> a >> b;
        graph.addEdge(i, a);
        graph.addEdge(i, b);
    }

    int result = graph.findMinCost(n);
    cout << result << endl;

    return 0;
}