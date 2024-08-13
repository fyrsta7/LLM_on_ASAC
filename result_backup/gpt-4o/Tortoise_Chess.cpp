#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    int N, M;
    cin >> N >> M;

    vector<int> scores(N + 1);
    for (int i = 1; i <= N; ++i) {
        cin >> scores[i];
    }

    vector<int> cards(M);
    for (int i = 0; i < M; ++i) {
        cin >> cards[i];
    }

    vector<vector<int>> dp(M + 1, vector<int>(N + 1, -1));
    dp[0][1] = scores[1]; // Start at position 1

    for (int i = 0; i < M; ++i) {
        for (int j = 1; j <= N; ++j) {
            if (dp[i][j] != -1) {
                if (j + cards[i] <= N) {
                    dp[i + 1][j + cards[i]] = max(dp[i + 1][j + cards[i]], dp[i][j] + scores[j + cards[i]]);
                }
            }
        }
    }

    int max_score = 0;
    for (int i = 1; i <= N; ++i) {
        max_score = max(max_score, dp[M][i]);
    }

    cout << max_score << endl;

    return 0;
}