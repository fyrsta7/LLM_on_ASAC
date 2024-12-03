#include <iostream>
#include <vector>
#include <set>
#include <algorithm>
#include <numeric>

using namespace std;

// Define the road structure
struct Road {
    int u, v, w;
};

// Union-Find data structure to keep track of connected components
struct UnionFind {
    vector<int> parent, rank;
    
    UnionFind(int n) {
        parent = vector<int>(n);
        rank = vector<int>(n, 0);
        iota(parent.begin(), parent.end(), 0);
    }
    
    int find(int u) {
        if (parent[u] != u) {
            parent[u] = find(parent[u]);
        }
        return parent[u];
    }
    
    bool unite(int u, int v) {
        int pu = find(u);
        int pv = find(v);
        if (pu != pv) {
            if (rank[pu] > rank[pv]) {
                parent[pv] = pu;
            } else if (rank[pu] < rank[pv]) {
                parent[pu] = pv;
            } else {
                parent[pu] = pv;
                rank[pv]++;
            }
            return true;
        }
        return false;
    }
};

// Check whether a set of roads forms a tree
bool isTree(const vector<Road> &roads, const set<int>& s, int n) {
    UnionFind uf(n);
    int count = 0;
    for (int r : s) {
        if (uf.unite(roads[r].u, roads[r].v)) {
            count++;
        }
    }
    return count == n - 1;
}

// Main function to solve the problem
int main() {
    int n, m;
    cin >> n >> m;
    
    // Reading the road data
    vector<Road> roads(n - 1);
    for (int i = 0; i < n - 1; ++i) {
        cin >> roads[i].u >> roads[i].v >> roads[i].w;
        roads[i].u--;
        roads[i].v--;
    }
    
    // Reading the race configurations
    vector<vector<int>> races(m);
    for (int i = 0; i < m; ++i) {
        int k;
        cin >> k;
        races[i].resize(k);
        for (int j = 0; j < k; ++j) {
            cin >> races[i][j];
            races[i][j]--;
        }
    }
    
    // Find the minimum length of the maximum path
    int min_len = INT_MAX;
    for (const vector<int>& race : races) {
        set<int> s(race.begin(), race.end());
        if (isTree(roads, s, n)) {
            int total_length = 0;
            for (int r : s) {
                total_length += roads[r].w;
            }
            min_len = min(min_len, total_length);
        }
    }
    
    // Output the result
    cout << min_len << endl;
    
    return 0;
}