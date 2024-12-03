#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    int n, m;
    cin >> n >> m;

    int max_mn = 1;
    for (int i = m; i <= m + n - 2; ++i) max_mn *= i;
    for (int i = 1; i <= n - 1; ++i) max_mn /= i;

    int max_t = 1 << (m * n);

    vector<vector<vector<int>>> table(max_t, vector<vector<int>>(n, vector<int>(m)));
    vector<vector<int>> direction(max_mn, vector<int>(m + n - 2));
    vector<vector<vector<int>>> track(max_t, vector<vector<int>>(max_mn, vector<int>(m + n - 1)));

    for (int t = 0; t < max_t; ++t) {
        for (int x = 0; x < n; ++x) {
            for (int y = 0; y < m; ++y) {
                table[t][x][y] = (t >> (x * m + y)) & 1;
            }
        }
    }

    int idx = 0;
    vector<int> dir(m + n - 2);
    for (int i = 0; i < n - 1; ++i) dir[i] = 0;
    for (int i = n - 1; i < m + n - 2; ++i) dir[i] = 1;

    do {
        direction[idx++] = dir;
    } while (next_permutation(dir.begin(), dir.end()));

    auto get_track = [](const vector<vector<int>>& t, const vector<int>& d) {
        vector<int> tmp(m + n - 1);
        tmp[0] = t[0][0];
        tmp[m + n - 1] = t[n - 1][m - 1];
        int x = 0, y = 0;
        for (int i = 1; i < m + n - 1; ++i) {
            if (d[i - 1] == 0) ++x;
            else ++y;
            tmp[i] = t[x][y];
        }
        return tmp;
    };

    for (int t = 0; t < max_t; ++t) {
        for (int i = 0; i < max_mn; ++i) {
            track[t][i] = get_track(table[t], direction[i]);
        }
    }

    vector<int> ans(max_t, 0);
    for (int t = 0; t < max_t; ++t) {
        bool valid = true;
        for (int i = 0; i < max_mn && valid; ++i) {
            for (int j = 0; j < max_mn && valid; ++j) {
                if (i != j) {
                    bool larger = false;
                    for (int k = 0; k < m + n - 2; ++k) {
                        if (direction[i][k] > direction[j][k]) {
                            larger = true;
                            break;
                        } else if (direction[i][k] < direction[j][k]) {
                            break;
                        }
                    }
                    if (larger) {
                        for (int k = 0; k < m + n - 2; ++k) {
                            if (track[t][i][k] < track[t][j][k]) {
                                valid = false;
                                break;
                            } else if (track[t][i][k] > track[t][j][k]) {
                                break;
                            }
                        }
                    }
                }
            }
        }
        if (valid) ans[t] = 1;
    }

    int sum_ans = 0;
    for (int t = 0; t < max_t; ++t) sum_ans += ans[t];

    cout << sum_ans << endl;

    return 0;
}