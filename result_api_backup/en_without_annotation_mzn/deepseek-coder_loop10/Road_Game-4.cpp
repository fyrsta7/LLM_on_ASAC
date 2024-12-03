#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    int n, m, p;
    cin >> n >> m >> p;
    
    vector<vector<int>> coins(n, vector<int>(m));
    vector<int> cost(n);
    
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            cin >> coins[i][j];
        }
    }
    
    for (int i = 0; i < n; ++i) {
        cin >> cost[i];
    }
    
    vector<int> dp(m + 1, -1e9);
    dp[0] = 0;
    
    for (int i = 1; i <= m; ++i) {
        vector<int> new_dp(m + 1, -1e9);
        for (int j = 0; j < i; ++j) {
            for (int k = 0; k < n; ++k) {
                int total_coins = 0;
                for (int l = 0; l < i - j; ++l) {
                    total_coins += coins[(k + l) % n][j + l];
                }
                new_dp[i] = max(new_dp[i], dp[j] + total_coins - cost[k]);
            }
        }
        dp = new_dp;
    }
    
    cout << dp[m] << endl;
    
    return 0;
}
