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

    vector<vector<int>> dp(T + 1, vector<int>(M + 1, 0));
    for (int i = 1; i <= T; ++i) {
        for (int j = 0; j <= M; ++j) {
            dp[i][j] = dp[i - 1][j];
            for (int k = 0; k < N; ++k) {
                if (j >= P[i - 1][k]) {
                    dp[i][j] = max(dp[i][j], dp[i - 1][j - P[i - 1][k]] + P[i - 1][k]);
                }
            }
        }
    }

    cout << M - dp[T][M] << endl;
    return 0;
}
