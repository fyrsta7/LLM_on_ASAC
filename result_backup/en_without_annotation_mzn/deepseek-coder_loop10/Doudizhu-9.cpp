#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>

using namespace std;

int main() {
    int T, n;
    cin >> T >> n;
    vector<vector<vector<int>>> cards(T, vector<vector<int>>(n, vector<int>(2)));
    for (int i = 0; i < T; ++i) {
        for (int j = 0; j < n; ++j) {
            cin >> cards[i][j][0] >> cards[i][j][1];
        }
    }

    vector<int> ans(T);

    for (int t = 0; t < T; ++t) {
        unordered_map<int, int> count;
        for (int i = 0; i < n; ++i) {
            count[cards[t][i][0]]++;
        }

        int valid_sets = 0;

        // Check for valid sets
        for (auto& [value, cnt] : count) {
            if (cnt == 2 || cnt == 3 || cnt == 4) {
                valid_sets++;
            } else if (cnt == 5) {
                int pair_count = 0;
                for (auto& [v, c] : count) {
                    if (c == 2) pair_count++;
                }
                if (pair_count == 2) valid_sets++;
            } else if (cnt >= 5) {
                bool is_straight = true;
                for (int i = 0; i < cnt - 1; ++i) {
                    if (count.find(value + i) == count.end() || count[value + i] != 1) {
                        is_straight = false;
                        break;
                    }
                }
                if (is_straight) valid_sets++;
            }
        }

        ans[t] = valid_sets;
    }

    for (int i = 0; i < T; ++i) {
        cout << ans[i] << endl;
    }

    return 0;
}
