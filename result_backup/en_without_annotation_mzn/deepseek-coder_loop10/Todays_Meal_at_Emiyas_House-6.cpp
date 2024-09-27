#include <iostream>
#include <vector>
#include <algorithm>

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
    int s = 0;

    auto valid_plan = [&](int idx) {
        vector<int> row_count(n, 0);
        vector<int> col_count(m, 0);
        for (int j = 0; j < dish_num[idx]; ++j) {
            int r = plans[idx][j][0];
            int c = plans[idx][j][1];
            if (a[r][c] <= 0 || row_count[r] > 0 || col_count[c] >= dish_num[idx] / 2) {
                return false;
            }
            row_count[r]++;
            col_count[c]++;
        }
        return true;
    };

    auto calculate_method = [&](int idx) {
        int method = 1;
        for (int j = 0; j < dish_num[idx]; ++j) {
            method = (1LL * method * a[plans[idx][j][0]][plans[idx][j][1]]) % MOD;
        }
        return method;
    };

    for (int i = 0; i < max_num; ++i) {
        dish_num[i] = __builtin_popcount(i);
        if (dish_num[i] > n) continue;
        for (int j = 0, mask = i; j < n; ++j, mask >>= 1) {
            plans[i][j][0] = j;
            plans[i][j][1] = mask & 1 ? 1 : 0;
        }
        if (valid_plan(i)) {
            methods[i] = calculate_method(i);
            s = (s + methods[i]) % MOD;
            num++;
        }
    }

    cout << s << endl;
    return 0;
}
