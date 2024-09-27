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

    vector<vector<long long>> dp(n + 1, vector<long long>(n + 1, 1e18));
    vector<vector<int>> best_k(n + 1, vector<int>(n + 1, 0));

    for (int i = 0; i <= n; ++i) {
        dp[i][0] = 0;
    }

    for (int j = 1; j <= n; ++j) {
        for (int i = 0; i <= n - j; ++i) {
            for (int k = 1; k <= j; ++k) {
                long long sum1 = prefix_sum[i + k] - prefix_sum[i];
                long long sum2 = prefix_sum[i + j] - prefix_sum[i + k];
                long long cost = sum1 * sum1 + dp[i + k][j - k];
                if (sum1 <= sum2 && cost < dp[i][j]) {
                    dp[i][j] = cost;
                    best_k[i][j] = k;
                }
            }
        }
    }

    cout << dp[0][n] << endl;

    return 0;
}
