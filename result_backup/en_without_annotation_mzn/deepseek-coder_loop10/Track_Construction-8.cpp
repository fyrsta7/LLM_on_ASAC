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

bool isConnected(const vector<Edge>& edges, int n) {
    UnionFind uf(n);
    for (const auto& e : edges) uf.unite(e.u, e.v);
    int root = uf.find(0);
    for (int i = 1; i < n; ++i) {
        if (uf.find(i) != root) return false;
    }
    return true;
}

int main() {
    int n, m;
    cin >> n >> m;
    vector<Edge> roads(n - 1);
    for (int i = 0; i < n - 1; ++i) {
        cin >> roads[i].u >> roads[i].v >> roads[i].w;
        --roads[i].u; --roads[i].v;
    }

    sort(roads.begin(), roads.end(), [](const Edge& a, const Edge& b) {
        return a.w < b.w;
    });

    int min_len = 0;
    for (int i = 0; i < m; ++i) {
        vector<Edge> race;
        UnionFind uf(n);
        for (const auto& e : roads) {
            if (!uf.same(e.u, e.v)) {
                uf.unite(e.u, e.v);
                race.push_back(e);
            }
        }
        if (isConnected(race, n)) {
            int race_len = 0;
            for (const auto& e : race) race_len += e.w;
            min_len = max(min_len, race_len);
        }
        rotate(roads.begin(), roads.begin() + 1, roads.end());
    }

    cout << min_len << endl;
    return 0;
}