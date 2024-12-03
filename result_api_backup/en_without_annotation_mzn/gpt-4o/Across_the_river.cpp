#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_set>
#include <climits>

using namespace std;

int minStones(int L, int S, int T, vector<int>& stones) {
    if (S == T) {
        unordered_set<int> stoneSet(stones.begin(), stones.end());
        int count = 0;
        for (int i = S; i <= L; i += S) {
            if (stoneSet.find(i) != stoneSet.end()) {
                count++;
            }
        }
        return count;
    }

    vector<int> dp(L + T + 1, INT_MAX);
    dp[0] = 0;
    unordered_set<int> stoneSet(stones.begin(), stones.end());

    for (int i = 0; i <= L + T; ++i) {
        if (dp[i] == INT_MAX) continue;
        for (int j = S; j <= T; ++j) {
            if (i + j > L + T) break;
            dp[i + j] = min(dp[i + j], dp[i] + (stoneSet.find(i + j) != stoneSet.end()));
        }
    }

    int ans = *min_element(dp.begin() + L, dp.begin() + L + T + 1);
    return ans;
}

int main() {
    int L, S, T, M;
    cin >> L >> S >> T >> M;

    vector<int> stones(M);
    for (int i = 0; i < M; ++i) {
        cin >> stones[i];
    }

    cout << minStones(L, S, T, stones) << endl;

    return 0;
}
