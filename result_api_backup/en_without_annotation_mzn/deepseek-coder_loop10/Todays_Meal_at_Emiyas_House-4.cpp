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

    auto valid_plan = [&](int plan_idx) {
        for (int i = 0; i < dish_num[plan_idx]; ++i) {
            if (a[plans[plan_idx][i][0]][plans[plan_idx][i][1]] <= 0) return false;
            for (int j = i + 1; j < dish_num[plan_idx]; ++j) {
                if (plans[plan_idx][i][0] == plans[plan_idx][j][0]) return false;
            }
        }
        for (int j = 0; j < m; ++j) {
            int count = 0;
            for (int k = 0; k < dish_num[plan_idx]; ++k) {
                if (plans[plan_idx][k][1] == j) ++count;
            }
            if (count > dish_num[plan_idx] / 2) return false;
        }
        return true;
    };

    auto calculate_method = [&](int plan_idx) {
        int method = 1;
        for (int j = 0; j < dish_num[plan_idx]; ++j) {
            method = (1LL * method * a[plans[plan_idx][j][0]][plans[plan_idx][j][1]]) % MOD;
        }
        return method;
    };

    for (int plan_idx = 0; plan_idx < max_num; ++plan_idx) {
        for (int i = 0; i < n; ++i) {
            plans[plan_idx][i][0] = i + 1;
            plans[plan_idx][i][1] = (plan_idx >> (i + 1)) % m + 1;
        }
        dish_num[plan_idx] = n;
        if (valid_plan(plan_idx)) {
            methods[plan_idx] = calculate_method(plan_idx);
            s = (s + methods[plan_idx]) % MOD;
            ++num;
        }
    }

    cout << s << endl;
    return 0;
}
