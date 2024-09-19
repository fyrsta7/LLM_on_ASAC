#include <iostream>
#include <vector>
using namespace std;

int main() {
    int n, m;
    cin >> n >> m;
    
    vector<vector<int>> dp(m + 1, vector<int>(n, 0));
    dp[0][0] = 1; // Starting at student 0 with 0 passes
    
    for (int i = 1; i <= m; ++i) {
        for (int j = 0; j < n; ++j) {
            dp[i][j] = dp[i - 1][(j - 1 + n) % n] + dp[i - 1][(j + 1) % n];
        }
    }
    
    cout << dp[m][0] << endl; // Output the ways to return to student 0
    return 0;
}