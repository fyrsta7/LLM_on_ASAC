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
    for (int i = 0; i < q; ++i) {
        cin >> order[i][0] >> order[i][1];
    }

    int L = 0;
    for (int i = 0; i < q; ++i) {
        L = max(L, order[i][1]);
    }

    vector<vector<vector<int>>> produce(q, vector<vector<int>>(n, vector<int>(L + 1, 0)));

    for (int i = 0; i < q; ++i) {
        produce[i][order[i][0] - 1][order[i][1]] = 1;
    }

    vector<vector<bool>> connected(n, vector<bool>(n, false));
    for (int i = 0; i < m; ++i) {
        connected[belt[i][0] - 1][belt[i][1] - 1] = true;
        connected[belt[i][1] - 1][belt[i][0] - 1] = true;
    }

    for (int i = 0; i < q; ++i) {
        for (int l = order[i][1] - 1; l >= 0; --l) {
            for (int j = 0; j < n; ++j) {
                for (int k = 0; k < n; ++k) {
                    if (j != k && connected[j][k]) {
                        produce[i][j][l] = max(produce[i][j][l], produce[i][k][l + 1]);
                    }
                }
            }
        }
    }

    for (int i = 0; i < q; ++i) {
        cout << (produce[i][0][0] > 0 ? "YES" : "NO") << endl;
    }

    return 0;
}
