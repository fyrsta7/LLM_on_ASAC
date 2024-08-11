#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>

using namespace std;

int main() {
    int n, d, k;
    cin >> n >> d >> k;

    vector<pair<int, int>> squares(n);
    vector<long long> prefix_sum(n + 1, 0);
    for (int i = 0; i < n; i++) {
        cin >> squares[i].first >> squares[i].second;
    }

    sort(squares.begin(), squares.end());

    for (int i = 0; i < n; i++) {
        prefix_sum[i + 1] = prefix_sum[i] + squares[i].second;
    }

    vector<long long> dp(n + 1, LLONG_MAX);
    dp[0] = 0;

    for (int i = 1; i <= n; i++) {
        for (int j = i - 1; j >= 0; j--) {
            if (squares[i - 1].first - squares[j].first < d) {
                if (prefix_sum[i] - prefix_sum[j] >= k) {
                    dp[i] = min(dp[i], dp[j] + squares[i - 1].first - squares[j].first);
                }
            } else {
                break;
            }
        }
    }

    long long ans = LLONG_MAX;
    for (int i = 0; i <= n; i++) {
        if (prefix_sum[n] - prefix_sum[i] >= k) {
            ans = min(ans, dp[i]);
        }
    }

    if (ans == LLONG_MAX) {
        cout << -1 << "\n";
    } else {
        cout << ans << "\n";
    }

    return 0;
}