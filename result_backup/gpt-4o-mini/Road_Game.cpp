#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    int n, m, p;
    cin >> n >> m >> p;

    vector<vector<int>> coins(n, vector<int>(m));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> coins[i][j];
        }
    }

    vector<int> cost(n);
    for (int i = 0; i < n; i++) {
        cin >> cost[i];
    }

    vector<vector<int>> dp(n + 1, vector<int>(m + 1, -1e9));
    
    for (int i = 0; i < n; i++) {
        dp[i][0] = 0; // No time means no collection
    }

    for (int time = 0; time < m; time++) {
        for (int start = 0; start < n; start++) {
            if (dp[start][time] < 0) continue;

            for (int steps = 1; steps <= p; steps++) {
                int end = (start + steps) % n;
                int collected = 0;

                // Sum gold collected
                for (int k = 0; k < steps; k++) {
                    collected += coins[start][(time + k) % m];
                    start = (start + 1) % n;
                }

                dp[end][time + steps] = max(dp[end][time + steps], dp[start][time] + collected - cost[start]);
            }
        }
    }

    int max_coins = -1e9;
    for (int i = 0; i < n; i++) {
        max_coins = max(max_coins, dp[i][m]);
    }

    cout << max_coins << endl;

    return 0;
}