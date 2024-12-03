#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

int main() {
    int n, m;
    cin >> n >> m;
    vector<vector<int>> matrix(n, vector<int>(m));
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < m; ++j)
            cin >> matrix[i][j];

    vector<vector<long long>> dp(n, vector<long long>(m + 1, 0));
    
    for (int j = 0; j < m; ++j) {
        for (int i = 0; i < n; ++i) {
            long long leftValue = (j == 0) ? 0 : dp[i][j];
            long long rightValue = (j == 0) ? 0 : dp[i][j];
            if (j > 0) {
                leftValue += matrix[i][0] * (1LL << j);
                rightValue += matrix[i][m - 1] * (1LL << j);
            }
            dp[i][j + 1] = max(dp[i][j + 1], leftValue);
            dp[i][j + 1] = max(dp[i][j + 1], rightValue);
        }
    }

    long long maxScore = 0;
    for (int i = 0; i < n; ++i)
        maxScore += dp[i][m];

    cout << maxScore << endl;
    return 0;
}