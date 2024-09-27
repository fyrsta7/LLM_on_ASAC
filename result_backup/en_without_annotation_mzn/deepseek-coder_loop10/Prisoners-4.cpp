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

    vector<vector<int>> dp(1 << N, vector<int>(2, INT_MAX));
    dp[0][0] = dp[0][1] = 0;

    for (int mask = 0; mask < (1 << N); ++mask) {
        for (int p = 0; p < 2; ++p) {
            if (dp[mask][p] == INT_MAX) continue;
            for (int i = 0; i < N; ++i) {
                if (mask & (1 << i)) continue;
                int new_mask = mask | (1 << i);
                int max_conflict = 0;
                for (int j = 0; j < M; ++j) {
                    if ((conflict[j][0] - 1 == i || conflict[j][1] - 1 == i) && (mask & (1 << (conflict[j][0] - 1))) && (mask & (1 << (conflict[j][1] - 1)))) {
                        max_conflict = max(max_conflict, conflict[j][2]);
                    }
                }
                dp[new_mask][p] = min(dp[new_mask][p], dp[mask][p]);
                dp[new_mask][1 - p] = min(dp[new_mask][1 - p], dp[mask][p] + max_conflict);
            }
        }
    }

    int final_value = min(dp[(1 << N) - 1][0], dp[(1 << N) - 1][1]);
    cout << final_value << endl;

    return 0;
}
