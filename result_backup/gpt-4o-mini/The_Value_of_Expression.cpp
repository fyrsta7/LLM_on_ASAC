#include <iostream>
#include <vector>
#include <string>

using namespace std;

const int MOD = 10007;

int countWays(const string &expr) {
    int n = expr.size();
    vector<vector<int>> dp0(n + 1, vector<int>(n + 1, 0));
    vector<vector<int>> dp1(n + 1, vector<int>(n + 1, 0));

    for (int len = 1; len <= n; len++) {
        for (int i = 0; i + len - 1 < n; i++) {
            int j = i + len - 1;

            if (len == 1) {
                dp0[i][j] = 1; // Either 0 or 1 can be placed.
                dp1[i][j] = 1; // Either 0 or 1 can be placed.
            } else {
                for (int k = i; k < j; k++) {
                    if (expr[k] == '+' || expr[k] == '*') {
                        int left0 = dp0[i][k - 1];
                        int left1 = dp1[i][k - 1];
                        int right0 = dp0[k + 1][j];
                        int right1 = dp1[k + 1][j];

                        if (expr[k] == '+') {
                            dp0[i][j] = (dp0[i][j] + left0 * right0) % MOD;
                            dp0[i][j] = (dp0[i][j] + left0 * right1) % MOD;
                            dp0[i][j] = (dp0[i][j] + left1 * right0) % MOD;
                            dp1[i][j] = (dp1[i][j] + left1 * right1) % MOD;
                        } else if (expr[k] == '*') {
                            dp0[i][j] = (dp0[i][j] + left0 * right0) % MOD;
                            dp0[i][j] = (dp0[i][j] + left0 * right1) % MOD;
                            dp0[i][j] = (dp0[i][j] + left1 * right0) % MOD;
                            dp1[i][j] = (dp1[i][j] + left1 * right1) % MOD;
                        }
                    }
                }
            }
        }
    }

    return dp0[0][n - 1];
}

int main() {
    int L;
    string expression;
    cin >> L >> expression;

    int result = countWays(expression);
    cout << result << endl;

    return 0;
}