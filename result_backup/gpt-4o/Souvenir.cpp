#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    int T, N, M;
    cin >> T >> N >> M;

    vector<vector<int>> prices(T, vector<int>(N));
    for (int i = 0; i < T; ++i) {
        for (int j = 0; j < N; ++j) {
            cin >> prices[i][j];
        }
    }

    vector<vector<int>> dp(T, vector<int>(M + 1, 0));
    for (int i = 0; i <= M; ++i) {
        dp[0][i] = i;
    }

    for (int i = 1; i < T; ++i) {
        for (int k = 0; k <= M; ++k) {
            dp[i][k] = dp[i-1][k];
            for (int j = 0; j < N; ++j) {
                int cost = prices[i-1][j];
                int income = prices[i][j];
                if (k >= cost) {
                    dp[i][k] = max(dp[i][k], dp[i-1][k-cost] + income);
                }
            }
        }
    }

    int maxCoins = 0;
    for (int i = 0; i <= M; ++i) {
        maxCoins = max(maxCoins, dp[T-1][i]);
    }

    cout << maxCoins << endl;
    return 0;
}
