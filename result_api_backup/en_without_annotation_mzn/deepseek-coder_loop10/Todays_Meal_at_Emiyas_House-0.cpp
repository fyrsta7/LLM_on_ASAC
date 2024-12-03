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

    int max_num = (1 << (n + m + 1));
    vector<vector<vector<int>>> plans(max_num, vector<vector<int>>(n, vector<int>(2)));
    vector<int> dish_num(max_num);
    vector<int> methods(max_num);
    int num = 0;
    int s = 0;

    for (int i = 0; i < max_num; ++i) {
        vector<int> dishes;
        for (int j = 0; j < n; ++j) {
            if (i & (1 << j)) {
                dishes.push_back(j);
            }
        }
        if (dishes.size() > 0) {
            bool valid = true;
            for (int j = 0; j < dishes.size(); ++j) {
                for (int k = j + 1; k < dishes.size(); ++k) {
                    if (dishes[j] == dishes[k]) {
                        valid = false;
                        break;
                    }
                }
                if (!valid) break;
            }
            if (valid) {
                int method = 1;
                for (int j = 0; j < dishes.size(); ++j) {
                    int dish = dishes[j];
                    for (int k = 0; k < m; ++k) {
                        if (a[dish][k] > 0) {
                            plans[num][j][0] = dish;
                            plans[num][j][1] = k;
                            method = (method * a[dish][k]) % MOD;
                        }
                    }
                }
                methods[num] = method;
                dish_num[num] = dishes.size();
                ++num;
            }
        }
    }

    for (int i = 0; i < num; ++i) {
        s = (s + methods[i]) % MOD;
    }

    cout << s << endl;
    return 0;
}
