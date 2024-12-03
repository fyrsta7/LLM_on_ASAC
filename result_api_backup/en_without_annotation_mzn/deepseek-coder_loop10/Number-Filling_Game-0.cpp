#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int n, m;

bool larger(const vector<int>& d1, const vector<int>& d2) {
    for (int i = 0; i < d1.size(); ++i) {
        if (d1[i] > d2[i]) return true;
        if (d1[i] < d2[i]) return false;
    }
    return false;
}

vector<int> get_track(const vector<vector<int>>& t, const vector<int>& d) {
    vector<int> tmp(m + n - 1);
    tmp[0] = t[0][0];
    tmp[m + n - 2] = t[n - 1][m - 1];
    for (int i = 1; i < m + n - 2; ++i) {
        int x = 0, y = 0;
        for (int j = 0; j < i; ++j) {
            if (d[j] == 0) ++x;
            else ++y;
        }
        tmp[i] = t[x][y];
    }
    return tmp;
}

int main() {
    cin >> n >> m;

    int max_mn = 1;
    for (int i = m; i <= m + n - 2; ++i) max_mn *= i;
    for (int i = 1; i <= n - 1; ++i) max_mn /= i;

    int max_t = 1 << (m * n);

    vector<vector<vector<int>>> table(max_t, vector<vector<int>>(n, vector<int>(m)));
    vector<vector<int>> direction(max_mn, vector<int>(m + n - 2));
    vector<vector<vector<int>>> track(max_t, vector<vector<int>>(max_mn, vector<int>(m + n - 1)));

    for (int i = 0; i < max_t; ++i) {
        int val = i;
        for (int x = 0; x < n; ++x) {
            for (int y = 0; y < m; ++y) {
                table[i][x][y] = val % 2;
                val /= 2;
            }
        }
    }

    int idx = 0;
    vector<int> dir(m + n - 2);
    for (int i = 0; i < (1 << (m + n - 2)); ++i) {
        int cnt0 = 0, cnt1 = 0;
        for (int j = 0; j < m + n - 2; ++j) {
            dir[j] = (i >> j) & 1;
            if (dir[j] == 0) ++cnt0;
            else ++cnt1;
        }
        if (cnt0 == n - 1 && cnt1 == m - 1) {
            direction[idx++] = dir;
        }
    }

    for (int t = 0; t < max_t; ++t) {
        for (int i = 0; i < max_mn; ++i) {
            track[t][i] = get_track(table[t], direction[i]);
        }
    }

    vector<int> ans(max_t);
    for (int t = 0; t < max_t; ++t) {
        bool valid = true;
        for (int i = 0; i < max_mn; ++i) {
            for (int j = 0; j < max_mn; ++j) {
                if (i != j && larger(direction[i], direction[j]) && !larger(track[t][i], track[t][j])) {
                    valid = false;
                    break;
                }
            }
            if (!valid) break;
        }
        ans[t] = valid ? 1 : 0;
    }

    int result = 0;
    for (int t = 0; t < max_t; ++t) {
        result += ans[t];
    }

    cout << result << endl;

    return 0;
}
