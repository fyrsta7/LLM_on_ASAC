#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    int n;
    cin >> n;
    vector<int> S(n);
    vector<int> A(n);
    for (int i = 0; i < n; ++i) cin >> S[i];
    for (int i = 0; i < n; ++i) cin >> A[i];

    vector<vector<int>> dp(n + 1, vector<int>(n + 1, -1));
    vector<vector<int>> choice(n + 1, vector<int>(n + 1, 0));

    dp[0][0] = 0;
    for (int i = 1; i <= n; ++i) {
        for (int j = 0; j <= n; ++j) {
            if (dp[i-1][j] != -1) {
                for (int k = 0; k <= n - j; ++k) {
                    int new_cost = dp[i-1][j] + A[k] + 2 * S[k];
                    if (new_cost > dp[i][j + k]) {
                        dp[i][j + k] = new_cost;
                        choice[i][j + k] = k;
                    }
                }
            }
        }
    }

    int max_cost = 0, max_index = 0;
    for (int i = 0; i <= n; ++i) {
        if (dp[n][i] > max_cost) {
            max_cost = dp[n][i];
            max_index = i;
        }
    }

    vector<int> c(n);
    for (int i = n; i > 0; --i) {
        c[i-1] = dp[i][max_index];
        max_index -= choice[i][max_index];
    }

    for (int i = 0; i < n; ++i) {
        cout << c[i] << " ";
    }
    cout << endl;

    return 0;
}