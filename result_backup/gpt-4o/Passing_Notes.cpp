#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    int m, n;
    cin >> m >> n;
    vector<vector<int>> kindness(m, vector<int>(n));

    for (int i = 0; i < m; ++i)
        for (int j = 0; j < n; ++j)
            cin >> kindness[i][j];

    vector<vector<vector<vector<int>>>> dp(m, vector<vector<vector<int>>>(n, vector<vector<int>>(m, vector<int>(n, -1e9))));

    dp[0][0][0][0] = kindness[0][0] * 2;

    for (int x1 = 0; x1 < m; ++x1) {
        for (int y1 = 0; y1 < n; ++y1) {
            for (int x2 = 0; x2 < m; ++x2) {
                int y2 = x1 + y1 - x2;
                if (y2 < 0 || y2 >= n) continue;
                int& cur = dp[x1][y1][x2][y2];
                if (x1 > 0 && x2 > 0) cur = max(cur, dp[x1-1][y1][x2-1][y2]);
                if (x1 > 0 && y2 > 0) cur = max(cur, dp[x1-1][y1][x2][y2-1]);
                if (y1 > 0 && x2 > 0) cur = max(cur, dp[x1][y1-1][x2-1][y2]);
                if (y1 > 0 && y2 > 0) cur = max(cur, dp[x1][y1-1][x2][y2-1]);
                if (x1 == 0 && y1 == 0) continue;
                if (x1 == x2 && y1 == y2) cur += kindness[x1][y1];
                else cur += kindness[x1][y1] + kindness[x2][y2];
            }
        }
    }
    cout << dp[m-1][n-1][m-1][n-1] - kindness[m-1][n-1] << endl;

    return 0;
}