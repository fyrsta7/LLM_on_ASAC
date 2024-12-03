#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_set>

using namespace std;

int main() {
    int L, S, T, M;
    cin >> L >> S >> T >> M;
    vector<int> stones(M);
    for (int i = 0; i < M; ++i) {
        cin >> stones[i];
    }
    sort(stones.begin(), stones.end());

    unordered_set<int> stone_set(stones.begin(), stones.end());
    vector<int> dp(L + T, M);
    dp[0] = 0;

    for (int i = 0; i < L; ++i) {
        for (int j = S; j <= T; ++j) {
            int next = i + j;
            if (next > L + T - 1) break;
            int stone_count = dp[i] + (stone_set.count(next) ? 1 : 0);
            dp[next] = min(dp[next], stone_count);
        }
    }

    int ans = M;
    for (int i = L; i < L + T; ++i) {
        ans = min(ans, dp[i]);
    }

    cout << ans << endl;
    return 0;
}