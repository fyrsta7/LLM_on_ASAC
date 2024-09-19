
```cpp
#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

constexpr int MOD = 998244353;

int main() {
    int n, m;
    cin >> n >> m;

    vector<vector<int>> a(n, vector<int>(m));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            cin >> a[i][j];
        }
    }

    vector<int> factorial(n + 1, 1);
    for (int i = 2; i <= n; ++i) {
        factorial[i] = (factorial[i - 1] * i) % MOD;
    }
    
    int result = 0;

    for (int mask = 1; mask < (1 << n); ++mask) {
        int count = __builtin_popcount(mask);
        vector<int> ingredientSum(m, 0);
        bool valid = true;

        for (int i = 0; i < n && valid; ++i) {
            if (mask & (1 << i)) {
                for (int j = 0; j < m; ++j) {
                    ingredientSum[j] += a[i][j];
                }
            }
        }

        for (int j = 0; j < m && valid; ++j) {
            if (ingredientSum[j] > count / 2) {
                valid = false;
            }
        }

        if (valid) {
            result = (result + factorial[count]) % MOD;
        }
    }

    cout << result << endl;
    return 0;
}
