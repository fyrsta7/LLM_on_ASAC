#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>

using namespace std;

const int MOD = 998244353;

int main() {
    int n, m;
    cin >> n >> m;
    vector<vector<int>> a(n, vector<int>(m));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            cin >> a[i][j];
        }
    }

    int max_num = 1 << (n + m + 1);
    vector<vector<vector<int>>> plans(max_num, vector<vector<int>>(n, vector<int>(2)));
    vector<int> dish_num(max_num);
    vector<int> methods(max_num);

    int num = 0;
    for (int i = 0; i < max_num; ++i) {
        vector<bool> used_rows(n, false);
        vector<int> row_count(m, 0);
        int method = 1;
        bool valid = true;

        for (int j = 0; j < n; ++j) {
            int row = (i >> (j * 2)) & 3;
            int col = (i >> (j * 2 + 1)) & 3;
            if (row >= n || col >= m || a[row][col] == 0 || used_rows[row] || row_count[col] >= (n + 1) / 2) {
                valid = false;
                break;
            }
            used_rows[row] = true;
            row_count[col]++;
            method = (1LL * method * a[row][col]) % MOD;
            plans[num][j][0] = row;
            plans[num][j][1] = col;
        }

        if (valid) {
            dish_num[num] = n;
            methods[num] = method;
            num++;
        }
    }

    int s = accumulate(methods.begin(), methods.begin() + num, 0LL) % MOD;
    cout << s << endl;

    return 0;
}
