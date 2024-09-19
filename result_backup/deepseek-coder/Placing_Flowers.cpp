#include <iostream>
#include <vector>
using namespace std;

const int MOD = 1000007;

int main() {
    int n, m;
    cin >> n >> m;
    vector<int> a(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }

    vector<vector<int>> dp(n + 1, vector<int>(m + 1, 0));
    dp[0][0] = 1;

    for (int i = 1; i <= n; ++i) {
        for (int j = 0; j <= m; ++j) {
            dp[i][j] = dp[i - 1][j];
            if (j >= 1) {
                dp[i][j] = (dp[i][j] + dp[i][j - 1]) % MOD;
            }
            if (j > a[i - 1]) {
                dp[i][j] = (dp[i][j] - dp[i - 1][j - a[i - 1] - 1] + MOD) % MOD;
            }
        }
    }

    cout << dp[n][m] << endl;
    return 0;
}
