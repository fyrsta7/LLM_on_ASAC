#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>

using namespace std;

int main() {
    int n, m;
    cin >> n >> m;
    vector<int> price(n + 1);
    for (int i = 1; i <= n; ++i) {
        cin >> price[i];
    }
    vector<vector<int>> roads(m, vector<int>(3));
    for (int i = 0; i < m; ++i) {
        cin >> roads[i][0] >> roads[i][1] >> roads[i][2];
    }

    vector<vector<bool>> available(n + 1, vector<bool>(n + 1, false));
    for (int i = 0; i < m; ++i) {
        available[roads[i][0]][roads[i][1]] = true;
        if (roads[i][2] == 2) {
            available[roads[i][1]][roads[i][0]] = true;
        }
    }

    vector<vector<int>> dp(n + 1, vector<int>(n + 1, INT_MIN));
    dp[1][1] = 0;

    for (int step = 1; step <= 2 * n; ++step) {
        vector<vector<int>> new_dp = dp;
        for (int i = 1; i <= n; ++i) {
            for (int j = 1; j <= n; ++j) {
                if (dp[i][j] != INT_MIN) {
                    for (int k = 1; k <= n; ++k) {
                        if (available[i][k]) {
                            new_dp[k][j] = max(new_dp[k][j], dp[i][j]);
                            if (j < step) {
                                new_dp[k][step] = max(new_dp[k][step], dp[i][j] + price[k] - price[i]);
                            }
                        }
                    }
                }
            }
        }
        dp = new_dp;
    }

    int max_income = 0;
    for (int i = 1; i <= n; ++i) {
        max_income = max(max_income, dp[n][i]);
    }

    cout << max_income << endl;
    return 0;
}