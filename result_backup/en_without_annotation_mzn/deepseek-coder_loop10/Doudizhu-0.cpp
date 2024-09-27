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
    for (int i = 0; i < T; ++i) {
        unordered_map<int, int> count;
        for (int j = 0; j < n; ++j) {
            count[cards[i][j][0]]++;
        }

        int valid_sets = 0;
        for (auto& [key, value] : count) {
            if (value > 0) {
                valid_sets++;
            }
        }

        ans[i] = valid_sets;
    }

    for (int i = 0; i < T; ++i) {
        cout << ans[i] << endl;
    }

    return 0;
}
