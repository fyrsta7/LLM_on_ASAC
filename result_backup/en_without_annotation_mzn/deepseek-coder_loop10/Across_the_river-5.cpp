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

    if (S == T) {
        int ans = 0;
        for (int stone : stones) {
            if (stone % S == 0) {
                ans++;
            }
        }
        cout << ans << endl;
        return 0;
    }

    sort(stones.begin(), stones.end());
    unordered_set<int> stone_set(stones.begin(), stones.end());

    vector<int> dp(L + T, L);
    dp[0] = 0;

    for (int i = 0; i < L + T; ++i) {
        for (int j = S; j <= T; ++j) {
            if (i + j < L + T) {
                dp[i + j] = min(dp[i + j], dp[i] + (stone_set.count(i + j) ? 1 : 0));
            }
        }
    }

    int ans = L;
    for (int i = L; i < L + T; ++i) {
        ans = min(ans, dp[i]);
    }

    cout << ans << endl;
    return 0;
}