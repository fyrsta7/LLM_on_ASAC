#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>

using namespace std;

const int MOD = 10007;

vector<vector<int>> graph;
vector<int> weight;
vector<int> subWeight;

void dfs(int node, int parent) {
    for (int neighbor : graph[node]) {
        if (neighbor != parent) {
            dfs(neighbor, node);
            subWeight[node] += subWeight[neighbor] + weight[neighbor];
        }
    }
    subWeight[node] += weight[node];
}

int main() {
    int n;
    cin >> n;
    
    graph.resize(n + 1);
    weight.resize(n + 1);
    subWeight.resize(n + 1, 0);
    
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        graph[u].push_back(v);
        graph[v].push_back(u);
    }
    
    for (int i = 1; i <= n; i++) {
        cin >> weight[i];
    }
    
    dfs(1, -1); // start DFS from node 1
    
    long long maxJointWeight = 0;
    long long jointWeightSum = 0;
    
    for (int u = 1; u <= n; u++) {
        for (int v : graph[u]) {
            if (subWeight[v] > 0) {
                long long pairWeight = static_cast<long long>(weight[u]) * weight[v];
                maxJointWeight = max(maxJointWeight, pairWeight);
                jointWeightSum = (jointWeightSum + pairWeight) % MOD;
            }
        }
    }
    
    cout << maxJointWeight << " " << jointWeightSum << endl;
    return 0;
}