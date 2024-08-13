#include <iostream>
#include <vector>
const int MOD = 1e9 + 7;

// Function to calculate the number of ways to fill the board
int countWays(int n, int m) {
    std::vector<std::vector<int>> dp(n + 1, std::vector<int>(m + 1, 0));
    dp[0][0] = 1;

    // Fill the dp table
    for (int i = 0; i <= n; ++i) {
        for (int j = 0; j <= m; ++j) {
            if (i > 0) {
                dp[i][j] = (dp[i][j] + dp[i-1][j]) % MOD;
            }
            if (j > 0) {
                dp[i][j] = (dp[i][j] + dp[i][j-1]) % MOD;
            }
        }
    }

    int totalCells = n * m;
    int totalWays = 1;
    
    // Calculate 2^(n*m) % MOD
    for (int i = 0; i < totalCells; ++i) {
        totalWays = (totalWays * 2) % MOD;
    }

    // Subtract 2^(n-1 * m-1) % MOD
    if (n > 1 && m > 1) {
        int subtractWays = 1;
        for (int i = 0; i < (n-1) * (m-1); ++i) {
            subtractWays = (subtractWays * 2) % MOD;
        }

        totalWays = (totalWays - subtractWays + MOD) % MOD;
    }

    return totalWays;
}

int main() {
    int n, m;
    std::cin >> n >> m;

    std::cout << countWays(n, m) << std::endl;

    return 0;
}