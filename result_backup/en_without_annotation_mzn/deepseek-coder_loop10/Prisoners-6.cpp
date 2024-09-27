#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>

using namespace std;

int main() {
    int N, M;
    cin >> N >> M;
    vector<vector<int>> conflict(M, vector<int>(3));
    for (int i = 0; i < M; ++i) {
        cin >> conflict[i][0] >> conflict[i][1] >> conflict[i][2];
    }

    vector<vector<int>> dp(1 << N, vector<int>(1 << N, INT_MAX));
    dp[0][0] = 0;

    for (int mask1 = 0; mask1 < (1 << N); ++mask1) {
        for (int mask2 = 0; mask2 < (1 << N); ++mask2) {
            if (mask1 & mask2) continue;
            int value1 = 0, value2 = 0;
            for (int i = 0; i < M; ++i) {
                if ((mask1 & (1 << (conflict[i][0] - 1))) && (mask1 & (1 << (conflict[i][1] - 1)))) {
                    value1 = max(value1, conflict[i][2]);
                }
                if ((mask2 & (1 << (conflict[i][0] - 1))) && (mask2 & (1 << (conflict[i][1] - 1)))) {
                    value2 = max(value2, conflict[i][2]);
                }
            }
            if (__builtin_popcount(mask1) < 2) value1 = 0;
            if (__builtin_popcount(mask2) < 2) value2 = 0;
            dp[mask1][mask2] = min(dp[mask1][mask2], max(value1, value2));
        }
    }

    int final_value = INT_MAX;
    for (int mask1 = 0; mask1 < (1 << N); ++mask1) {
        int mask2 = ((1 << N) - 1) ^ mask1;
        final_value = min(final_value, dp[mask1][mask2]);
    }

    cout << final_value << endl;
    return 0;
}
