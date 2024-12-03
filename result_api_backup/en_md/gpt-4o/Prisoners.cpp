#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct Edge {
    int u, v, cost;
};

bool compareEdges(const Edge& a, const Edge& b) {
    return a.cost < b.cost;
}

class DisjointSet {
public:
    DisjointSet(int n) {
        parent.resize(n);
        rank.resize(n, 0);
        for (int i = 0; i < n; i++) {
            parent[i] = i;
        }
    }
    
    int find(int u) {
        if (u != parent[u]) {
            parent[u] = find(parent[u]);
        }
        return parent[u];
    }
    
    void unionSets(int u, int v) {
        int rootU = find(u);
        int rootV = find(v);
        if (rootU != rootV) {
            if (rank[rootU] > rank[rootV]) {
                parent[rootV] = rootU;
            } else if (rank[rootU] < rank[rootV]) {
                parent[rootU] = rootV;
            } else {
                parent[rootV] = rootU;
                rank[rootU]++;
            }
        }
    }
    
private:
    vector<int> parent;
    vector<int> rank;
};

int main() {
    int N, M;
    cin >> N >> M;
    
    vector<Edge> edges(M);
    for (int i = 0; i < M; i++) {
        cin >> edges[i].u >> edges[i].v >> edges[i].cost;
        edges[i].u--;
        edges[i].v--;
    }
    
    sort(edges.begin(), edges.end(), compareEdges);
    
    DisjointSet ds(N);
    for (const auto& edge : edges) {
        if (ds.find(edge.u) != ds.find(edge.v)) {
            ds.unionSets(edge.u, edge.v);
        } else {
            cout << edge.cost << endl;
            return 0;
        }
    }
    
    cout << "0" << endl;
    return 0;
}