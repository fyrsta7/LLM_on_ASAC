#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    int n;
    cin >> n;
    vector<int> h(n);
    for (int i = 0; i < n; ++i) {
        cin >> h[i];
    }

    int max_h = *max_element(h.begin(), h.end());
    int max_action = n * max_h;

    vector<vector<int>> dp(n + 1, vector<int>(max_h + 1, max_action));
    dp[0][0] = 0;

    for (int i = 1; i <= n; ++i) {
        for (int j = 0; j <= max_h; ++j) {
            for (int k = 0; k <= j; ++k) {
                dp[i][j] = min(dp[i][j], dp[i - 1][k] + (j - k));
            }
        }
    }

    int actions = max_action;
    for (int j = h[n - 1]; j <= max_h; ++j) {
        actions = min(actions, dp[n][j]);
    }

    cout << actions << endl;

    return 0;
}
