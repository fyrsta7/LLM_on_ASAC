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
    
    vector<vector<int>> dp(m + 1, vector<int>(n, -1e9));
    vector<vector<int>> next_location(m + 1, vector<int>(n));
    
    for (int i = 0; i < n; ++i) {
        dp[0][i] = 0;
    }
    
    for (int i = 1; i <= m; ++i) {
        for (int j = 0; j < n; ++j) {
            for (int k = 0; k < n; ++k) {
                int new_location = (j + k) % n;
                int new_value = dp[i - 1][j] + coins[new_location][i - 1] - cost[k];
                if (new_value > dp[i][new_location]) {
                    dp[i][new_location] = new_value;
                    next_location[i][new_location] = j;
                }
            }
        }
    }
    
    int max_benefit = -1e9;
    int best_location = 0;
    
    for (int i = 0; i < n; ++i) {
        if (dp[m][i] > max_benefit) {
            max_benefit = dp[m][i];
            best_location = i;
        }
    }
    
    cout << max_benefit << endl;
    
    return 0;
}
