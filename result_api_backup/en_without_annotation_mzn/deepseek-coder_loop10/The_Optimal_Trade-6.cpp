#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>

using namespace std;

int main() {
    int n, m;
    cin >> n >> m;
    vector<int> price(n + 1);
    for (int i = 1; i <= n; ++i) {
        cin >> price[i];
    }
    vector<vector<pair<int, int>>> roads(n + 1);
    for (int i = 0; i < m; ++i) {
        int u, v, t;
        cin >> u >> v >> t;
        roads[u].push_back({v, t});
        roads[v].push_back({u, t});
    }

    vector<int> dp(n + 1, INT_MIN);
    dp[1] = 0;
    for (int i = 1; i <= n; ++i) {
        for (auto& road : roads[i]) {
            int j = road.first;
            int t = road.second;
            if (t == 1) {
                dp[j] = max(dp[j], dp[i]);
            } else {
                dp[j] = max(dp[j], dp[i] + price[j] - price[i]);
            }
        }
    }

    cout << max(0, dp[n]) << endl;
    return 0;
}