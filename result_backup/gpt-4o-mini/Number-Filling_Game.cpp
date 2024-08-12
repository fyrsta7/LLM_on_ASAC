#include <iostream>
#include <vector>

using namespace std;

const int MOD = 1e9 + 7;

int countWays(int n, int m) {
    vector<vector<int>> dp(n + 1, vector<int>(m + 1, 0));
    
    dp[0][0] = 1; // Starting point
    
    for (int i = 0; i <= n; ++i) {
        for (int j = 0; j <= m; ++j) {
            if (i < n) {
                dp[i + 1][j] = (dp[i + 1][j] + dp[i][j]) % MOD; // Move down
            }
            if (j < m) {
                dp[i][j + 1] = (dp[i][j + 1] + dp[i][j]) % MOD; // Move right
            }
        }
    }

    // The valid paths count is in dp[n][m]
    return dp[n][m];
}

int main() {
    int n, m;
    cin >> n >> m;
    
    int result = countWays(n - 1, m - 1);
    
    cout << result << endl;
    
    return 0;
}