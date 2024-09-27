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
    vector<vector<int>> choose(n + 1, vector<int>(n + 1, 0));
    dp[0][0] = 0;

    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= i; ++j) {
            int cost = A[j - 1] + S[j - 1] * 2;
            if (dp[i - 1][j - 1] + cost > dp[i - 1][j]) {
                dp[i][j] = dp[i - 1][j - 1] + cost;
                choose[i][j] = 1;
            } else {
                dp[i][j] = dp[i - 1][j];
                choose[i][j] = 0;
            }
        }
    }

    vector<int> r(n);
    vector<int> c(n);
    int max_cost = -1e9, max_j = 0;
    for (int j = 1; j <= n; ++j) {
        if (dp[n][j] > max_cost) {
            max_cost = dp[n][j];
            max_j = j;
        }
    }

    for (int i = n; i > 0; --i) {
        if (choose[i][max_j] == 1) {
            r[i - 1] = max_j;
            c[i - 1] = A[max_j - 1] + S[max_j - 1] * 2;
            max_j--;
        } else {
            r[i - 1] = 0;
            c[i - 1] = 0;
        }
    }

    for (int i = 0; i < n; ++i) {
        cout << c[i] << " ";
    }
    cout << endl;

    return 0;
}