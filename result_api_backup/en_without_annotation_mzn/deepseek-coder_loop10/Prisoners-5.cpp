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

    vector<vector<int>> adj(N + 1, vector<int>(N + 1, 0));
    for (int i = 0; i < M; ++i) {
        adj[conflict[i][0]][conflict[i][1]] = conflict[i][2];
        adj[conflict[i][1]][conflict[i][0]] = conflict[i][2];
    }

    vector<int> dp(1 << N, INT_MAX);
    dp[0] = 0;

    for (int mask = 0; mask < (1 << N); ++mask) {
        if (dp[mask] == INT_MAX) continue;
        for (int i = 0; i < N; ++i) {
            if (mask & (1 << i)) continue;
            int new_mask = mask | (1 << i);
            int max_conflict = 0;
            for (int j = 0; j < N; ++j) {
                if (mask & (1 << j)) {
                    max_conflict = max(max_conflict, adj[i + 1][j + 1]);
                }
            }
            dp[new_mask] = min(dp[new_mask], max(dp[mask], max_conflict));
        }
    }

    int final_value = INT_MAX;
    for (int mask = 0; mask < (1 << N); ++mask) {
        int complement_mask = ((1 << N) - 1) ^ mask;
        final_value = min(final_value, max(dp[mask], dp[complement_mask]));
    }

    cout << final_value << endl;
    return 0;
}