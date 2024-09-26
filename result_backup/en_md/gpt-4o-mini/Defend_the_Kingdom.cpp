#include <iostream>
#include <vector>
#include <queue>
#include <limits>
using namespace std;

struct Edge {
    int to;
};

// Global variables
vector<vector<Edge>> graph;
vector<int> cost;
vector<int> degree;

int dfs(int node, int parent, bool required_node1, bool required_node2) {
    int total_cost = 0;

    if (required_node1) {
        total_cost += cost[node];
    } else if (required_node2) {
        total_cost += cost[node];
    } else {
        bool has_child_with_troops = false;

        for (const auto& edge : graph[node]) {
            if (edge.to != parent) {
                int child_cost = dfs(edge.to, node, false, false);
                if (child_cost >= 0) {
                    has_child_with_troops = true;
                    total_cost += child_cost;
                } else {
                    return -1; // Unreachable
                }
            }
        }

        // If this node must not have troops and no child has troops, we must station at this node
        if (!required_node1 && !required_node2 && !has_child_with_troops) {
            total_cost += cost[node];
        }
    }
    return total_cost;
}

int main() {
    int n, m;
    string type;
    cin >> n >> m >> type;
    
    cost.resize(n);
    for (int i = 0; i < n; ++i) {
        cin >> cost[i];
    }

    graph.resize(n);
    degree.resize(n, 0);
    
    for (int i = 0; i < n - 1; ++i) {
        int u, v;
        cin >> u >> v;
        --u; --v; // Use zero-indexing
        graph[u].push_back({v});
        graph[v].push_back({u});
        degree[u]++;
        degree[v]++;
    }

    for (int j = 0; j < m; ++j) {
        int a, x, b, y;
        cin >> a >> x >> b >> y;
        --a; --b; // Use zero-indexing
        if ((x == 1 && y == 1 && degree[a] + degree[b] == 0) || 
            (x == 0 && y == 0 && (degree[a] == 0 || degree[b] == 0)) ||
            (x == 1 && y == 0 && b != a && degree[b] == 0) ||
            (x == 0 && y == 1 && a != b && degree[a] == 0)) {
            cout << -1 << endl;
            continue;
        }
        
        int total_cost = 0;
        if (x == 1) total_cost += cost[a];
        if (y == 1) total_cost += cost[b];
        
        int cost_for_children = dfs(a, -1, x == 1, y == 1);
        if (cost_for_children < 0) {
            cout << -1 << endl;
        } else {
            cout << total_cost + cost_for_children << endl;
        }
    }

    return 0;
}