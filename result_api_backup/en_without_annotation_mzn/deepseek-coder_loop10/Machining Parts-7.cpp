#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

int main() {
    int n, m, q;
    cin >> n >> m >> q;

    vector<vector<int>> belt(m, vector<int>(2));
    for (int i = 0; i < m; ++i) {
        cin >> belt[i][0] >> belt[i][1];
    }

    vector<vector<int>> order(q, vector<int>(2));
    int L = 0;
    for (int i = 0; i < q; ++i) {
        cin >> order[i][0] >> order[i][1];
        L = max(L, order[i][1]);
    }

    vector<vector<vector<int>>> produce(q, vector<vector<int>>(n, vector<int>(L + 1, 0)));
    vector<vector<bool>> connected(n, vector<bool>(n, false));

    for (int i = 0; i < m; ++i) {
        int u = belt[i][0] - 1;
        int v = belt[i][1] - 1;
        connected[u][v] = connected[v][u] = true;
    }

    for (int i = 0; i < q; ++i) {
        int start = order[i][0] - 1;
        int time = order[i][1];
        produce[i][start][time] = 1;

        for (int t = time - 1; t >= 0; --t) {
            for (int j = 0; j < n; ++j) {
                for (int k = 0; k < n; ++k) {
                    if (j != k && connected[j][k]) {
                        produce[i][j][t] = produce[i][k][t + 1];
                    }
                }
            }
        }
    }

    for (int i = 0; i < q; ++i) {
        if (produce[i][0][0] > 0) {
            cout << "YES\n";
        } else {
            cout << "NO\n";
        }
    }

    return 0;
}
