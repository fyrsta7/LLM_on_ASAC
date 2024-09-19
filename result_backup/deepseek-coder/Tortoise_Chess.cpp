#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int N, M;
vector<int> scores;
vector<int> cards;
vector<vector<int>> dp;

int main() {
    cin >> N >> M;
    scores.resize(N + 1);
    cards.resize(M);
    dp.resize(M + 1, vector<int>(N + 1, -1));

    for (int i = 1; i <= N; ++i) {
        cin >> scores[i];
    }
    for (int i = 0; i < M; ++i) {
        cin >> cards[i];
    }

    dp[0][1] = scores[1];
    for (int i = 0; i < M; ++i) {
        for (int j = 1; j <= N; ++j) {
            if (dp[i][j] != -1) {
                for (int k = i; k < M; ++k) {
                    int next = j + cards[k];
                    if (next <= N) {
                        dp[i + 1][next] = max(dp[i + 1][next], dp[i][j] + scores[next]);
                    }
                }
            }
        }
    }

    int maxScore = 0;
    for (int i = 1; i <= M; ++i) {
        maxScore = max(maxScore, dp[i][N]);
    }

    cout << maxScore << endl;
    return 0;
}
