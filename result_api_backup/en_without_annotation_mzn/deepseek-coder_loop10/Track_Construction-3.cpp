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

bool connected(const vector<Road>& roads, int n) {
    UnionFind uf(n);
    for (const auto& road : roads) {
        uf.merge(road.u, road.v);
    }
    int root = uf.find(0);
    for (int i = 1; i < n; ++i) {
        if (uf.find(i) != root) return false;
    }
    return true;
}

int main() {
    int n, m;
    cin >> n >> m;
    vector<Road> roads(n - 1);
    for (int i = 0; i < n - 1; ++i) {
        cin >> roads[i].u >> roads[i].v >> roads[i].w;
        --roads[i].u;
        --roads[i].v;
    }

    sort(roads.begin(), roads.end(), [](const Road& a, const Road& b) {
        return a.w < b.w;
    });

    int min_len = 0;
    for (int i = 0; i < (1 << (n - 1)); ++i) {
        vector<Road> subset;
        for (int j = 0; j < n - 1; ++j) {
            if (i & (1 << j)) {
                subset.push_back(roads[j]);
            }
        }
        if (subset.size() == m && connected(subset, n)) {
            int len = 0;
            for (const auto& road : subset) {
                len += road.w;
            }
            min_len = max(min_len, len);
        }
    }

    cout << min_len << endl;
    return 0;
}