#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <set>

using namespace std;

struct Road {
    int u, v, w;
};

class UnionFind {
    vector<int> parent, rank;
public:
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
    vector<Road> roads(n - 1);
    for (int i = 0; i < n - 1; ++i) {
        cin >> roads[i].u >> roads[i].v >> roads[i].w;
    }

    sort(roads.begin(), roads.end(), [](const Road& a, const Road& b) {
        return a.w < b.w;
    });

    int max_min_len = 0;
    for (int mask = 0; mask < (1 << (n - 1)); ++mask) {
        UnionFind uf(n + 1);
        int min_len = INT_MAX;
        bool valid = true;
        for (int i = 0; i < n - 1; ++i) {
            if (mask & (1 << i)) {
                if (uf.same(roads[i].u, roads[i].v)) {
                    valid = false;
                    break;
                }
                uf.unite(roads[i].u, roads[i].v);
                min_len = min(min_len, roads[i].w);
            }
        }
        if (valid) {
            max_min_len = max(max_min_len, min_len);
        }
    }

    cout << max_min_len << endl;
    return 0;
}
