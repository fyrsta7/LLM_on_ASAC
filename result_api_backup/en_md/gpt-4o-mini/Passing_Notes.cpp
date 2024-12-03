#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int maxKindness(const vector<vector<int>>& matrix, int m, int n) {
    vector<vector<int>> dp1(m, vector<int>(n, 0)), dp2(m, vector<int>(n, 0));
    
    // Calculate max kindness path from top-left to bottom-right
    dp1[0][0] = 0; 
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            if (i > 0) dp1[i][j] = max(dp1[i][j], dp1[i - 1][j] + matrix[i][j]);
            if (j > 0) dp1[i][j] = max(dp1[i][j], dp1[i][j - 1] + matrix[i][j]);
        }
    }

    // Calculate max kindness path from bottom-right to top-left
    dp2[m - 1][n - 1] = 0; 
    for (int i = m - 1; i >= 0; --i) {
        for (int j = n - 1; j >= 0; --j) {
            if (i < m - 1) dp2[i][j] = max(dp2[i][j], dp2[i + 1][j] + matrix[i][j]);
            if (j < n - 1) dp2[i][j] = max(dp2[i][j], dp2[i][j + 1] + matrix[i][j]);
        }
    }

    // Calculate the maximum kindness sum from both paths
    int maxSum = 0;
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            maxSum = max(maxSum, dp1[i][j] + dp2[i][j]);
        }
    }

    return maxSum;
}

int main() {
    int m, n;
    cin >> m >> n;
    vector<vector<int>> matrix(m, vector<int>(n));
    
    for (int i = 0; i < m; ++i)
        for (int j = 0; j < n; ++j)
            cin >> matrix[i][j];

    int result = maxKindness(matrix, m, n);
    cout << result << endl;

    return 0;
}