#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    int n, m, p;
    cin >> n >> m >> p;

    vector<vector<int>> coins(n, vector<int>(m));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            cin >> coins[i][j];
        }
    }

    vector<int> costs(n);
    for (int i = 0; i < n; ++i) {
        cin >> costs[i];
    }

    int max_coins = INT_MIN;
    for (int start = 0; start < n; ++start) {
        vector<int> dp(m + 1, INT_MIN);
        dp[0] = 0;

        for (int walk = 1; walk <= p; ++walk) {
            vector<int> new_dp(m + 1, INT_MIN);
            for (int time = 0; time < m; ++time) {
                if (dp[time] != INT_MIN) {
                    for (int step = 1; step <= walk; ++step) {
                        if (time + step <= m) {
                            int collected = 0;
                            for (int i = 0; i < step; ++i) {
                                collected += coins[(start + time + i) % n][time + i];
                            }
                            new_dp[time + step] = max(new_dp[time + step], dp[time] + collected);
                        }
                    }
                }
            }
            dp = new_dp;
        }

        for (int time = 0; time <= m; ++time) {
            if (dp[time] != INT_MIN) {
                max_coins = max(max_coins, dp[time] - costs[start]);
            }
        }
    }

    cout << max_coins << endl;
    return 0;
}
