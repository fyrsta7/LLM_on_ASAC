#include <iostream>
using namespace std;

int ballPassingWays(int n, int m) {
    int dp[m + 1][n];
    for (int i = 0; i < n; ++i) dp[0][i] = (i == 0) ? 1 : 0;

    for (int j = 1; j <= m; ++j) {
        for (int i = 0; i < n; ++i) {
            dp[j][i] = dp[j - 1][(i - 1 + n) % n] + dp[j - 1][(i + 1) % n];
        }
    }

    return dp[m][0];
}

int main() {
    int n, m;
    cin >> n >> m;
    cout << ballPassingWays(n, m) << endl;
    return 0;
}