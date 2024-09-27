#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>

using namespace std;

int main() {
    int n;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; ++i) cin >> a[i];

    vector<long long> prefix_sum(n + 1, 0);
    for (int i = 0; i < n; ++i) {
        prefix_sum[i + 1] = prefix_sum[i] + a[i];
    }

    vector<vector<long long>> dp(n + 1, vector<long long>(n + 1, LLONG_MAX));
    vector<vector<int>> best_k(n + 1, vector<int>(n + 1, 0));

    for (int i = 1; i <= n; ++i) {
        dp[i][1] = prefix_sum[i] * prefix_sum[i];
        best_k[i][1] = 0;
    }

    for (int j = 2; j <= n; ++j) {
        for (int i = j; i <= n; ++i) {
            for (int k = best_k[i - 1][j - 1]; k < i; ++k) {
                long long cost = dp[k][j - 1] + (prefix_sum[i] - prefix_sum[k]) * (prefix_sum[i] - prefix_sum[k]);
                if (cost < dp[i][j]) {
                    dp[i][j] = cost;
                    best_k[i][j] = k;
                }
            }
        }
    }

    long long ans = LLONG_MAX;
    for (int j = 1; j <= n; ++j) {
        ans = min(ans, dp[n][j]);
    }

    cout << ans << endl;
    return 0;
}
