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

    vector<vector<int>> dp(n + 1, vector<int>(n + 1, -1e9));
    vector<vector<int>> choice(n + 1, vector<int>(n + 1, 0));
    dp[0][0] = 0;

    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= i; ++j) {
            int cost = A[j - 1] + S[j - 1] * 2;
            for (int k = 0; k < i; ++k) {
                if (dp[i][j] < dp[i - 1][k] + cost) {
                    dp[i][j] = dp[i - 1][k] + cost;
                    choice[i][j] = k;
                }
            }
        }
    }

    int max_cost = -1e9, idx = 0;
    for (int j = 1; j <= n; ++j) {
        if (dp[n][j] > max_cost) {
            max_cost = dp[n][j];
            idx = j;
        }
    }

    vector<int> c(n);
    for (int i = n; i > 0; --i) {
        c[i - 1] = dp[i][idx];
        idx = choice[i][idx];
    }

    for (int i = 0; i < n; ++i) {
        cout << c[i] << " ";
    }
    cout << endl;

    return 0;
}