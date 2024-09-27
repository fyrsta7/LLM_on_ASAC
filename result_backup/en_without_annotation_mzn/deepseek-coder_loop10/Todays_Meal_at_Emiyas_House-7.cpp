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

    for (int i = 0; i < max_num; ++i) {
        vector<int> dish_count(m, 0);
        bool valid = true;
        int method = 1;

        for (int j = 0; j < n; ++j) {
            int x = (i >> (j * 2)) & 3;
            if (x >= m) {
                valid = false;
                break;
            }
            plans[i][j][0] = j;
            plans[i][j][1] = x;
            if (a[j][x] == 0) {
                valid = false;
                break;
            }
            method = (1LL * method * a[j][x]) % MOD;
            dish_count[x]++;
        }

        if (!valid) continue;

        for (int j = 0; j < m; ++j) {
            if (dish_count[j] > n / 2) {
                valid = false;
                break;
            }
        }

        if (valid) {
            dish_num[num] = n;
            methods[num] = method;
            num++;
            s = (s + method) % MOD;
        }
    }

    cout << s << endl;

    return 0;
}
