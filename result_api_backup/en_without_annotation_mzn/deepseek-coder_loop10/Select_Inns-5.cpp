#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    int n, k, p;
    cin >> n >> k >> p;
    vector<pair<int, int>> hotel(n);
    for (int i = 0; i < n; ++i) {
        cin >> hotel[i].first >> hotel[i].second;
    }

    vector<vector<int>> dp(n, vector<int>(n, 0));
    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n; ++j) {
            if (hotel[i].first == hotel[j].first) {
                bool valid = false;
                for (int t = i; t <= j; ++t) {
                    if (hotel[t].second <= p) {
                        valid = true;
                        break;
                    }
                }
                if (valid) {
                    dp[i][j] = 1;
                }
            }
        }
    }

    vector<int> dp2(n, 0);
    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n; ++j) {
            if (dp[i][j]) {
                dp2[j] = max(dp2[j], dp2[i] + 1);
            }
        }
    }

    int max_num = 0;
    for (int i = 0; i < n; ++i) {
        max_num = max(max_num, dp2[i]);
    }

    cout << max_num << endl;
    return 0;
}
