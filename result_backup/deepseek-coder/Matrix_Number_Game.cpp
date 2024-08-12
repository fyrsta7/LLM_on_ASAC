#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

int main() {
    int n, m;
    cin >> n >> m;
    vector<vector<int>> matrix(n, vector<int>(m));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            cin >> matrix[i][j];
        }
    }

    vector<vector<long long>> dp(m, vector<long long>(2, 0));
    long long maxScore = 0;

    for (int i = 0; i < n; ++i) {
        vector<vector<long long>> new_dp(m, vector<long long>(2, 0));
        for (int j = 0; j < m; ++j) {
            if (j > 0) {
                new_dp[j][0] = max(new_dp[j][0], new_dp[j-1][0]);
                new_dp[j][1] = max(new_dp[j][1], new_dp[j-1][1]);
            }
            new_dp[j][0] = max(new_dp[j][0], dp[j][0] + matrix[i][j] * (1LL << (j + 1)));
            new_dp[j][1] = max(new_dp[j][1], dp[j][1] + matrix[i][m-1-j] * (1LL << (j + 1)));
        }
        dp = new_dp;
    }

    for (int i = 0; i < m; ++i) {
        maxScore = max(maxScore, max(dp[i][0], dp[i][1]));
    }

    cout << maxScore << endl;
    return 0;
}
