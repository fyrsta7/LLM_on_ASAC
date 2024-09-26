#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    int n;
    cin >> n;
    vector<int> d(n);
    for (int i = 0; i < n; ++i) {
        cin >> d[i];
    }

    int max_action = n * *max_element(d.begin(), d.end());
    vector<vector<int>> state(max_action + 1, vector<int>(n, 0));
    vector<pair<int, int>> left_right(max_action + 1);

    for (int i = 0; i < n; ++i) {
        state[0][i] = d[i];
    }

    int actions = 0;
    for (int i = 0; i < n; ++i) {
        while (state[actions][i] > 0) {
            int left = i;
            int right = i;
            while (right < n && state[actions][right] > 0) {
                state[actions + 1][right] = state[actions][right] - 1;
                ++right;
            }
            for (int j = left; j < right; ++j) {
                state[actions + 1][j] = state[actions][j] - 1;
            }
            for (int j = 0; j < left; ++j) {
                state[actions + 1][j] = state[actions][j];
            }
            for (int j = right; j < n; ++j) {
                state[actions + 1][j] = state[actions][j];
            }
            left_right[actions] = {left + 1, right};
            ++actions;
        }
    }

    cout << actions << endl;
    return 0;
}
