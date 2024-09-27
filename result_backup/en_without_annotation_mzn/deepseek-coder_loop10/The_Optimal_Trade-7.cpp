#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>

using namespace std;

int main() {
    int n, m;
    cin >> n >> m;
    vector<int> price(n + 1);
    for (int i = 1; i <= n; ++i) cin >> price[i];

    vector<vector<int>> roads(n + 1, vector<int>(n + 1, INT_MAX));
    for (int i = 0; i < m; ++i) {
        int u, v, t;
        cin >> u >> v >> t;
        roads[u][v] = 1;
        if (t == 2) roads[v][u] = 1;
    }

    vector<vector<int>> dp(n + 1, vector<int>(n + 1, INT_MIN));
    dp[1][1] = 0;

    for (int k = 1; k <= n; ++k) {
        for (int i = 1; i <= n; ++i) {
            for (int j = 1; j <= n; ++j) {
                if (roads[i][j] == 1 && dp[k - 1][i] != INT_MIN) {
                    dp[k][j] = max(dp[k][j], dp[k - 1][i]);
                    if (k > 1) {
                        dp[k][j] = max(dp[k][j], dp[k - 1][j]);
                        dp[k][j] = max(dp[k][j], dp[k - 1][i] + price[j] - price[i]);
                    }
                }
            }
        }
    }

    int maxIncome = 0;
    for (int k = 1; k <= n; ++k) {
        maxIncome = max(maxIncome, dp[k][n]);
    }

    cout << maxIncome << endl;
    return 0;
}