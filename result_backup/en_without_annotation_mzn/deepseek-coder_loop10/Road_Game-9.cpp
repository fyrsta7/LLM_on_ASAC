#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    int n, m, p;
    cin >> n >> m >> p;

    vector<vector<int>> coins(n, vector<int>(m));
    vector<int> cost(n);

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            cin >> coins[i][j];
        }
    }

    for (int i = 0; i < n; ++i) {
        cin >> cost[i];
    }

    vector<int> dp(m + 1, -1e9);
    dp[0] = 0;

    for (int i = 1; i <= m; ++i) {
        for (int j = 0; j < n; ++j) {
            int total_coins = 0;
            for (int k = 0; k < p && i - k >= 1; ++k) {
                total_coins += coins[(j + k) % n][i - k - 1];
                dp[i] = max(dp[i], dp[i - k - 1] + total_coins - cost[j]);
            }
        }
    }

    cout << dp[m] << endl;

    return 0;
}
