#include <iostream>
#include <vector>
#include <algorithm>
#include <limits>

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

    vector<int> dp(1 << N, numeric_limits<int>::max());
    dp[0] = 0;

    for (int mask = 0; mask < (1 << N); ++mask) {
        for (int i = 0; i < N; ++i) {
            if (!(mask & (1 << i))) {
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
    }

    cout << dp[(1 << N) - 1] << endl;
    return 0;
}