#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <set>

using namespace std;

struct Road {
    int u, v, w;
};

class UnionFind {
public:
    UnionFind(int n) : parent(n), rank(n, 0) {
        iota(parent.begin(), parent.end(), 0);
    }

    int find(int x) {
        if (parent[x] != x) parent[x] = find(parent[x]);
        return parent[x];
    }

    bool unite(int x, int y) {
        x = find(x);
        y = find(y);
        if (x == y) return false;
        if (rank[x] < rank[y]) swap(x, y);
        parent[y] = x;
        if (rank[x] == rank[y]) rank[x]++;
        return true;
    }

private:
    vector<int> parent, rank;
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

    int min_len = 0;
    UnionFind uf(n + 1);
    set<int> used_roads;

    for (int i = 0; i < m; ++i) {
        int max_weight = 0;
        for (int j = 0; j < n - 1; ++j) {
            if (used_roads.count(j)) continue;
            if (uf.unite(roads[j].u, roads[j].v)) {
                max_weight = roads[j].w;
                used_roads.insert(j);
            }
        }
        min_len = max(min_len, max_weight);
    }

    cout << min_len << endl;
    return 0;
}
