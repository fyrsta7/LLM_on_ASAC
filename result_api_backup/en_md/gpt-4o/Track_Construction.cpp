#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
using namespace std;

struct Edge {
    int to, length;
};

vector<vector<Edge>> graph;
vector<int> subtreeSize;

int getMaxTrackLength(int n, int m) {
    vector<int> lengths;
    
    function<int(int, int)> dfs = [&](int node, int parent) -> int {
        priority_queue<int> q;
        int totalNodesInSubtree = 1;
        
        for (auto& edge : graph[node]) {
            if (edge.to == parent) continue;
            int subtreeResult = dfs(edge.to, node);
            totalNodesInSubtree += subtreeSize[edge.to];
            lengths.push_back(edge.length + subtreeResult);
            q.push(edge.length + subtreeResult);
        }
        
        int maxLength = 0;
        if (m > 1 && !q.empty()) {
            length = max(length, q.top());
            q.pop();
        }
        if (m > 2 && !q.empty()) {
            length = max(length, length + q.top());
        }
        
        subtreeSize[node] = totalNodesInSubtree;
        return maxLength;
    };
    
    subtreeSize.resize(n + 1, 0);
    int result = dfs(1, -1);
    
    sort(lengths.rbegin(), lengths.rend());
    return lengths[m - 1];
}

int main() {
    int n, m;
    cin >> n >> m;
    
    graph.resize(n + 1);
    
    for (int i = 0; i < n - 1; ++i) {
        int a, b, l;
        cin >> a >> b >> l;
        graph[a].push_back({b, l});
        graph[b].push_back({a, l});
    }
    
    cout << getMaxTrackLength(n, m) << endl;
    
    return 0;
}