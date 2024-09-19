#include <iostream>
#include <vector>
using namespace std;

vector<int> countCombinations(int k, int w) {
    vector<int> result(k + 1, 0);
    int max_segments = w / k;
    vector<vector<int>> dp(max_segments + 1, vector<int>(1 << k, 0));
    dp[0][0] = 1;

    for (int seg = 1; seg <= max_segments; ++seg) {
        for (int mask = 0; mask < (1 << k); ++mask) {
            for (int prev_mask = 0; prev_mask < (1 << k); ++prev_mask) {
                if ((mask & prev_mask) == prev_mask && (mask ^ prev_mask) > 0) {
                    dp[seg][mask] += dp[seg - 1][prev_mask];
                }
            }
        }
        result[seg] = dp[seg][(1 << k) - 1];
    }

    return result;
}

int main() {
    int k, w;
    cin >> k >> w;

    vector<int> combinations = countCombinations(k, w);
    int total = 0;
    for (int i = 2; i <= k; ++i) {
        total += combinations[i];
    }

    cout << total << endl;
    return 0;
}
