#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    int T, N, M;
    cin >> T >> N >> M;
    vector<vector<int>> P(T, vector<int>(N));
    for (int i = 0; i < T; ++i) {
        for (int j = 0; j < N; ++j) {
            cin >> P[i][j];
        }
    }

    vector<int> dp(M + 1, 0);
    for (int i = 0; i < T; ++i) {
        vector<int> new_dp(M + 1, 0);
        for (int j = 0; j <= M; ++j) {
            new_dp[j] = dp[j];
            for (int k = 0; k < N; ++k) {
                if (j >= P[i][k]) {
                    new_dp[j] = max(new_dp[j], dp[j - P[i][k]] + P[i][k]);
                }
            }
        }
        dp = new_dp;
    }

    cout << dp[M] << endl;
    return 0;
}