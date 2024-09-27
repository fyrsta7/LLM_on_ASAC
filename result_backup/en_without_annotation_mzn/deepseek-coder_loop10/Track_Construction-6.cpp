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
            if (rank[x] == rank[y]) rank[x]++;
        }
    }

    bool same(int x, int y) {
        return find(x) == find(y);
    }
};

bool isConnected(const vector<Road>& roads, int n) {
    UnionFind uf(n);
    for (const auto& road : roads) {
        uf.unite(road.u, road.v);
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
        roads[i].u--;
        roads[i].v--;
    }

    sort(roads.begin(), roads.end(), [](const Road& a, const Road& b) {
        return a.w < b.w;
    });

    int min_len = 0;
    for (int i = 0; i < m; ++i) {
        vector<Road> selectedRoads;
        UnionFind uf(n);
        for (const auto& road : roads) {
            if (!uf.same(road.u, road.v)) {
                uf.unite(road.u, road.v);
                selectedRoads.push_back(road);
            }
        }
        if (isConnected(selectedRoads, n)) {
            int len = 0;
            for (const auto& road : selectedRoads) {
                len += road.w;
            }
            min_len = max(min_len, len);
        }
    }

    cout << min_len << endl;
    return 0;
}