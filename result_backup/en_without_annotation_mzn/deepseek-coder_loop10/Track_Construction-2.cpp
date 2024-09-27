#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
#include <queue>

using namespace std;

struct Edge {
    int u, v, w;
};

class UnionFind {
public:
    UnionFind(int n) : parent(n), rank(n, 0) {
        for (int i = 0; i < n; ++i) parent[i] = i;
    }

    int find(int x) {
        if (parent[x] != x) parent[x] = find(parent[x]);
        return parent[x];
    }

    void unite(int x, int y) {
        int rootX = find(x);
        int rootY = find(y);
        if (rootX != rootY) {
            if (rank[rootX] > rank[rootY]) parent[rootY] = rootX;
            else if (rank[rootX] < rank[rootY]) parent[rootX] = rootY;
            else {
                parent[rootY] = rootX;
                rank[rootX]++;
            }
        }
    }

private:
    vector<int> parent, rank;
};

int main() {
    int n, m;
    cin >> n >> m;
    vector<Edge> edges(n - 1);
    for (int i = 0; i < n - 1; ++i) {
        cin >> edges[i].u >> edges[i].v >> edges[i].w;
        edges[i].u--;
        edges[i].v--;
    }

    sort(edges.begin(), edges.end(), [](const Edge &a, const Edge &b) {
        return a.w < b.w;
    });

    int max_min_len = 0;
    for (int mask = 0; mask < (1 << (n - 1)); ++mask) {
        UnionFind uf(n);
        int min_len = INT_MAX;
        bool valid = true;
        for (int i = 0; i < n - 1; ++i) {
            if (mask & (1 << i)) {
                if (uf.find(edges[i].u) == uf.find(edges[i].v)) {
                    valid = false;
                    break;
                }
                uf.unite(edges[i].u, edges[i].v);
                min_len = min(min_len, edges[i].w);
            }
        }
        if (valid) {
            max_min_len = max(max_min_len, min_len);
        }
    }

    cout << max_min_len << endl;
    return 0;
}