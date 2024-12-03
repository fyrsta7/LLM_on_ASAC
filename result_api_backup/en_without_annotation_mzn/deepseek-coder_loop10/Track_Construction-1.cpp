#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <set>

using namespace std;

struct Edge {
    int u, v, w;
};

class UnionFind {
public:
    vector<int> parent, rank;
    UnionFind(int n) {
        parent.resize(n);
        rank.resize(n, 0);
        for (int i = 0; i < n; ++i) parent[i] = i;
    }
    int find(int x) {
        if (parent[x] != x) parent[x] = find(parent[x]);
        return parent[x];
    }
    void unite(int x, int y) {
        x = find(x);
        y = find(y);
        if (x == y) return;
        if (rank[x] < rank[y]) parent[x] = y;
        else {
            parent[y] = x;
            if (rank[x] == rank[y]) ++rank[x];
        }
    }
    bool same(int x, int y) {
        return find(x) == find(y);
    }
};

int main() {
    int n, m;
    cin >> n >> m;
    vector<Edge> edges(n - 1);
    for (int i = 0; i < n - 1; ++i) {
        cin >> edges[i].u >> edges[i].v >> edges[i].w;
    }

    sort(edges.begin(), edges.end(), [](const Edge& a, const Edge& b) {
        return a.w < b.w;
    });

    int max_min_len = 0;
    for (int mask = 0; mask < (1 << (n - 1)); ++mask) {
        UnionFind uf(n + 1);
        int min_len = INT_MAX;
        bool valid = true;
        for (int i = 0; i < n - 1; ++i) {
            if (mask & (1 << i)) {
                if (uf.same(edges[i].u, edges[i].v)) {
                    valid = false;
                    break;
                }
                uf.unite(edges[i].u, edges[i].v);
                min_len = min(min_len, edges[i].w);
            }
        }
        if (valid && uf.find(1) == uf.find(n)) {
            max_min_len = max(max_min_len, min_len);
        }
    }

    cout << max_min_len << endl;
    return 0;
}