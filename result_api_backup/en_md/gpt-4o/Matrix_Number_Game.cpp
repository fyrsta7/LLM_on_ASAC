#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

long long maxScore(vector<vector<int>> &matrix, int n, int m) {
    vector<vector<vector<long long>>> dp(n, vector<vector<long long>>(m, vector<long long>(m, 0)));

    // Base case for the first removal (i = 1)
    for (int row = 0; row < n; ++row) {
        dp[row][0][0] = matrix[row][0]; // only one element can be chosen, from left or right (both are same in base case)
    }

    for (int i = 1; i < m; ++i) {
        for (int row = 0; row < n; ++row) {
            for (int l = 0; l <= i; ++l) {
                int r = i - l;

                if (l < m && r < m) {
                    long long leftScore = (l > 0 ? dp[row][l-1][r] : 0) + ((1LL << i) * matrix[row][l]);
                    long long rightScore = (r > 0 ? dp[row][l][r-1] : 0) + ((1LL << i) * matrix[row][m-1-r]);

                    dp[row][l][r] = max(leftScore, rightScore);
                }
            }
        }
    }

    long long maxScore = 0;
    for (int row = 0; row < n; ++row) {
        maxScore += dp[row][m-1][m-1];
    }

    return maxScore;
}

int main() {
    int n, m;
    cin >> n >> m;
    vector<vector<int>> matrix(n, vector<int>(m));

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            cin >> matrix[i][j];
        }
    }

    cout << maxScore(matrix, n, m) << endl;
    return 0;
}