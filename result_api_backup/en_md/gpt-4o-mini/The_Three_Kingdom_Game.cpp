#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>

using namespace std;

int main() {
    int N;
    cin >> N;

    // Read bonding levels into a matrix
    vector<vector<int>> bonding(N, vector<int>(N, 0));
    for (int i = 0; i < N; ++i) {
        for (int j = i + 1; j < N; ++j) {
            cin >> bonding[i][j];
            bonding[j][i] = bonding[i][j]; // since the bonding level is symmetric
        }
    }

    vector<bool> dp(1 << N, false);
    dp[0] = true;
    int maxBonding = INT_MIN;

    for (int mask = 0; mask < (1 << N); ++mask) {
        int selectedCount = __builtin_popcount(mask);
        if (selectedCount % 2 != 0 || selectedCount > N) continue;

        int xiaoHanGenerals = selectedCount / 2;
        int compGenerals = selectedCount - xiaoHanGenerals;

        if (compGenerals > xiaoHanGenerals) {
            int bestChoice = INT_MIN;

            // Computer evaluates the best pairing to block Xiao Han
            for (int i = 0; i < N; ++i) {
                if (!(mask & (1 << i))) {
                    // Evaluate pairing with Xiao Han's generals
                    for (int j = 0; j < N; ++j) {
                        if (mask & (1 << j)) {
                            if (xiaoHanGenerals > 0) {
                                bestChoice = max(bestChoice, bonding[i][j]);
                            }
                        }
                    }
                }
            }

            for (int i = 0; i < N; ++i) {
                if (!(mask & (1 << i))) {
                    // Free general chosen
                    int newMask = mask | (1 << i);
                    if (!dp[newMask]) {
                        dp[newMask] = true;
                        maxBonding = max(maxBonding, bestChoice);
                    }
                }
            }
        }
    }

    if (maxBonding == INT_MIN) {
        cout << 0 << endl;
    } else {
        cout << 1 << endl;
        cout << maxBonding << endl;
    }

    return 0;
}