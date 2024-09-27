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
    vector<vector<int>> partition(n + 1, vector<int>(n + 1, 0));

    for (int i = 1; i <= n; ++i) {
        dp[i][1] = prefix_sum[i] * prefix_sum[i];
        partition[i][1] = 0;
    }

    for (int k = 2; k <= n; ++k) {
        for (int i = k; i <= n; ++i) {
            for (int j = k - 1; j < i; ++j) {
                long long cost = dp[j][k - 1] + (prefix_sum[i] - prefix_sum[j]) * (prefix_sum[i] - prefix_sum[j]);
                if (cost < dp[i][k]) {
                    dp[i][k] = cost;
                    partition[i][k] = j;
                }
            }
        }
    }

    long long ans = LLONG_MAX;
    int part_num = 0;
    for (int k = 1; k <= n; ++k) {
        if (dp[n][k] < ans) {
            ans = dp[n][k];
            part_num = k;
        }
    }

    cout << ans << endl;

    return 0;
}
