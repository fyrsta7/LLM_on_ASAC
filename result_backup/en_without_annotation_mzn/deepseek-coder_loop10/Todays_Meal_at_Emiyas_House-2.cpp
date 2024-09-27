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
    int s = 0;

    auto valid_plan = [&](int idx) {
        for (int i = 0; i < dish_num[idx]; ++i) {
            if (a[plans[idx][i][0]][plans[idx][i][1]] <= 0) return false;
            for (int j = i + 1; j < dish_num[idx]; ++j) {
                if (plans[idx][i][0] == plans[idx][j][0]) return false;
            }
        }
        for (int j = 0; j < m; ++j) {
            int count = 0;
            for (int i = 0; i < dish_num[idx]; ++i) {
                if (plans[idx][i][1] == j) ++count;
            }
            if (count > dish_num[idx] / 2) return false;
        }
        return true;
    };

    auto calculate_methods = [&](int idx) {
        int method = 1;
        for (int i = 0; i < dish_num[idx]; ++i) {
            method = (1LL * method * a[plans[idx][i][0]][plans[idx][i][1]]) % MOD;
        }
        return method;
    };

    for (int idx = 1; idx < max_num; ++idx) {
        dish_num[idx] = __builtin_popcount(idx);
        int k = 0;
        for (int i = 0; i < n + m; ++i) {
            if (idx & (1 << i)) {
                plans[idx][k][0] = i < n ? i : i - n;
                plans[idx][k][1] = i < n ? 0 : i - n;
                ++k;
            }
        }
        if (valid_plan(idx)) {
            methods[idx] = calculate_methods(idx);
            s = (s + methods[idx]) % MOD;
            ++num;
        }
    }

    cout << s << endl;
    return 0;
}
