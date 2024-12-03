#include <iostream>
#include <vector>
#include <queue>
using namespace std;

struct Edge {
    int u, v;
};

struct Query {
    int factory, units;
};

int main() {
    int n, m, q;
    cin >> n >> m >> q;

    vector<Edge> belts(m);
    for (int i = 0; i < m; i++) {
        cin >> belts[i].u >> belts[i].v;
    }

    vector<Query> orders(q);
    int L = 0;
    for (int i = 0; i < q; i++) {
        cin >> orders[i].factory >> orders[i].units;
        L = max(L, orders[i].units);
    }

    for (int i = 0; i < q; i++) {
        vector<vector<int>> produce(n + 1, vector<int>(L + 1, 0));
        produce[orders[i].factory][0] = orders[i].units;

        queue<int> bfs;
        bfs.push(orders[i].factory);

        while (!bfs.empty()) {
            int current = bfs.front();
            bfs.pop();

            for (const auto& belt : belts) {
                if (belt.u == current || belt.v == current) {
                    int next = (belt.u == current) ? belt.v : belt.u;
                    if (produce[next][0] == 0) {
                        produce[next][0] = produce[current][0];
                        bfs.push(next);
                    }
                }
            }
        }

        if (produce[1][0] > 0) {
            cout << "YES\n";
        } else {
            cout << "NO\n";
        }
    }

    return 0;
}
