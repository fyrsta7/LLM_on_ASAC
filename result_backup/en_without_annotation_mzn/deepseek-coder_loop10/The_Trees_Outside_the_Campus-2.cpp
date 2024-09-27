#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    int L, M;
    cin >> L >> M;
    vector<pair<int, int>> spots(M);
    for (int i = 0; i < M; ++i) {
        cin >> spots[i].first >> spots[i].second;
    }

    sort(spots.begin(), spots.end(), [](const pair<int, int>& a, const pair<int, int>& b) {
        return a.second < b.second;
    });

    vector<int> dp(L + 1, 0);
    int last_end = -1;

    for (const auto& spot : spots) {
        for (int i = last_end + 1; i <= spot.second; ++i) {
            dp[i] = dp[last_end + 1];
        }
        dp[spot.second] = max(dp[spot.second], (spot.first > 0 ? dp[spot.first - 1] : 0) + spot.second - spot.first + 1);
        last_end = spot.second;
    }

    for (int i = last_end + 1; i <= L; ++i) {
        dp[i] = dp[last_end + 1];
    }

    cout << dp[L] << endl;
    return 0;
}