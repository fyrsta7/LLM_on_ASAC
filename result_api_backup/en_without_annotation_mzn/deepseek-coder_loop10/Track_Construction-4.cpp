#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
#include <queue>

using namespace std;

struct Road {
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
    int find(int u) {
        if (u != parent[u]) parent[u] = find(parent[u]);
        return parent[u];
    }
    void merge(int u, int v) {
        u = find(u);
        v = find(v);
        if (u == v) return;
        if (rank[u] > rank[v]) parent[v] = u;
        else {
            parent[u] = v;
            if (rank[u] == rank[v]) ++rank[v];
        }
    }
};

int main() {
    int n, m;
    cin >> n >> m;
    vector<Road> roads(n - 1);
    for (int i = 0; i < n - 1; ++i) {
        cin >> roads[i].u >> roads[i].v >> roads[i].w;
    }

    sort(roads.begin(), roads.end(), [](const Road &a, const Road &b) {
        return a.w < b.w;
    });

    int max_min_len = 0;
    for (int i = 0; i < (1 << (n - 1)); ++i) {
        UnionFind uf(n + 1);
        int min_len = INT_MAX;
        bool valid = true;
        for (int j = 0; j < n - 1; ++j) {
            if (i & (1 << j)) {
                if (uf.find(roads[j].u) == uf.find(roads[j].v)) {
                    valid = false;
                    break;
                }
                uf.merge(roads[j].u, roads[j].v);
                min_len = min(min_len, roads[j].w);
            }
        }
        if (valid) {
            max_min_len = max(max_min_len, min_len);
        }
    }

    cout << max_min_len << endl;
    return 0;
}