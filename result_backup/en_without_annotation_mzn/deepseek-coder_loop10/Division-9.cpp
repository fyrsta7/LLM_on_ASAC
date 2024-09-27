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

    vector<long long> dp(n + 1, LLONG_MAX);
    vector<int> best_k(n + 1, 0);
    dp[0] = 0;

    for (int i = 1; i <= n; ++i) {
        for (int j = 0; j < i; ++j) {
            long long sum_j_to_i = prefix_sum[i] - prefix_sum[j];
            long long cost = dp[j] + sum_j_to_i * sum_j_to_i;
            if (cost < dp[i]) {
                dp[i] = cost;
                best_k[i] = j;
            }
        }
    }

    cout << dp[n] << endl;

    return 0;
}
