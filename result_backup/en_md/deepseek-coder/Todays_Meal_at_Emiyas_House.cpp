#include <iostream>
#include <vector>
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

    vector<vector<int>> dp(n + 1, vector<int>(n + 1, 0));
    dp[0][0] = 1;
    for (int i = 1; i <= n; ++i) {
        for (int j = 0; j <= i; ++j) {
            dp[i][j] = dp[i - 1][j];
            if (j > 0) {
                dp[i][j] = (dp[i][j] + dp[i - 1][j - 1]) % MOD;
            }
        }
    }

    int ans = 0;
    for (int k = 1; k <= n; ++k) {
        vector<vector<int>> ways(m, vector<int>(k + 1, 0));
        for (int j = 0; j < m; ++j) {
            ways[j][0] = 1;
            for (int i = 0; i < n; ++i) {
                for (int l = k - 1; l >= 0; --l) {
                    if (ways[j][l] && a[i][j]) {
                        ways[j][l + 1] = (ways[j][l + 1] + 1LL * ways[j][l] * a[i][j]) % MOD;
                    }
                }
            }
        }

        vector<int> sum(k + 1, 0);
        for (int j = 0; j < m; ++j) {
            for (int l = 0; l <= k; ++l) {
                sum[l] = (sum[l] + ways[j][l]) % MOD;
            }
        }

        for (int l = 0; l <= k; ++l) {
            if (l <= k / 2) {
                ans = (ans + 1LL * dp[n][k] * sum[l]) % MOD;
            } else {
                ans = (ans + 1LL * dp[n][k] * (sum[l] - sum[l - k / 2 - 1] + MOD)) % MOD;
            }
        }
    }

    cout << ans << endl;
    return 0;
}
