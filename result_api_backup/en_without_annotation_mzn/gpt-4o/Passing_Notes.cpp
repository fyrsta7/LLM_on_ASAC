#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    int m, n;
    cin >> m >> n;
    
    vector<vector<int>> students(m, vector<int>(n));
    for (int i = 0; i < m; ++i)
        for (int j = 0; j < n; ++j)
            cin >> students[i][j];
    
    vector<vector<int>> dp1(m, vector<int>(n, 0));
    dp1[0][0] = students[0][0];

    for (int i = 1; i < m; ++i)
        dp1[i][0] = dp1[i-1][0] + students[i][0];

    for (int j = 1; j < n; ++j)
        dp1[0][j] = dp1[0][j-1] + students[0][j];

    for (int i = 1; i < m; ++i)
        for (int j = 1; j < n; ++j)
            dp1[i][j] = max(dp1[i-1][j], dp1[i][j-1]) + students[i][j];

    vector<vector<int>> dp2(m, vector<int>(n, 0));
    dp2[m-1][n-1] = students[m-1][n-1];

    for (int i = m-2; i >= 0; --i)
        dp2[i][n-1] = dp2[i+1][n-1] + students[i][n-1];

    for (int j = n-2; j >= 0; --j)
        dp2[m-1][j] = dp2[m-1][j+1] + students[m-1][j];

    for (int i = m-2; i >= 0; --i)
        for (int j = n-2; j >= 0; --j)
            dp2[i][j] = max(dp2[i+1][j], dp2[i][j+1]) + students[i][j];

    int max_value = 0;
    for (int i = 0; i < m; ++i)
        for (int j = 0; j < n; ++j)
            if (i == 0 && j == 0 && i == m-1 && j == n-1)
                max_value = max(max_value, dp1[i][j] + dp2[i][j] - students[i][j]);
            else if (i == 0 && j == 0)
                max_value = max(max_value, dp2[i][j] + dp1[i+1][j+1]);
            else if (i == m-1 && j == n-1)
                max_value = max(max_value, dp1[i][j] + dp2[i-1][j-1]);
            else
                max_value = max(max_value, dp1[i][j] + dp2[i][j]);

    cout << max_value << endl;
    return 0;
}