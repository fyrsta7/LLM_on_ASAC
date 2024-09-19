#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    int n, m, p;
    cin >> n >> m >> p;

    vector<vector<int>> gold(n, vector<int>(m));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            cin >> gold[i][j];
        }
    }

    vector<int> cost(n);
    for (int i = 0; i < n; ++i) {
        cin >> cost[i];
    }

    vector<int> dp(m + 1, -1e9);
    dp[0] = 0;

    for (int t = 0; t < m; ++t) {
        vector<int> new_dp(m + 1, -1e9);

        for (int i = 0; i < n; ++i) {
            int collected = 0;
            for (int j = 0; j < p && t + j < m; ++j) {
                collected += gold[(i + j) % n][t + j];
                new_dp[t + j + 1] = max(new_dp[t + j + 1], dp[t] + collected - cost[i]);
            }
        }

        dp = new_dp;
    }

    int max_gold = *max_element(dp.begin(), dp.end());
    cout << max_gold << endl;

    return 0;
}
