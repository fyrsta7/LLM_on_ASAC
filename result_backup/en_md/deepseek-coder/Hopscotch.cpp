#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

const int INF = 1e9;

int main() {
    int n, d, k;
    cin >> n >> d >> k;
    vector<pair<int, int>> squares(n);
    for (int i = 0; i < n; ++i) {
        cin >> squares[i].first >> squares[i].second;
    }

    vector<int> dp(n, -INF);
    dp[0] = squares[0].second;
    int max_score = dp[0];

    for (int i = 1; i < n; ++i) {
        for (int j = 0; j < i; ++j) {
            int dist = squares[i].first - squares[j].first;
            if (dist >= d) {
                dp[i] = max(dp[i], dp[j] + squares[i].second);
            }
        }
        max_score = max(max_score, dp[i]);
    }

    if (max_score >= k) {
        cout << 0 << endl;
        return 0;
    }

    int low = 0, high = d - 1;
    while (low < high) {
        int mid = (low + high) / 2;
        vector<int> dp_new(n, -INF);
        dp_new[0] = squares[0].second;
        int max_score_new = dp_new[0];

        for (int i = 1; i < n; ++i) {
            for (int j = 0; j < i; ++j) {
                int dist = squares[i].first - squares[j].first;
                if (dist >= d - mid) {
                    dp_new[i] = max(dp_new[i], dp_new[j] + squares[i].second);
                }
            }
            max_score_new = max(max_score_new, dp_new[i]);
        }

        if (max_score_new >= k) {
            high = mid;
        } else {
            low = mid + 1;
        }
    }

    vector<int> dp_new(n, -INF);
    dp_new[0] = squares[0].second;
    int max_score_new = dp_new[0];

    for (int i = 1; i < n; ++i) {
        for (int j = 0; j < i; ++j) {
            int dist = squares[i].first - squares[j].first;
            if (dist >= d - low) {
                dp_new[i] = max(dp_new[i], dp_new[j] + squares[i].second);
            }
        }
        max_score_new = max(max_score_new, dp_new[i]);
    }

    if (max_score_new >= k) {
        cout << low << endl;
    } else {
        cout << -1 << endl;
    }

    return 0;
}
