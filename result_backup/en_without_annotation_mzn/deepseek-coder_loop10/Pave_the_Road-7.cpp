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
    for (int i = 0; i < n; ++i) {
        state[0][i] = d[i];
    }

    int actions = 0;
    for (int i = 0; i < n; ++i) {
        while (state[actions][i] > 0) {
            int left = i;
            while (left > 0 && state[actions][left - 1] > 0) {
                --left;
            }
            int right = i;
            while (right < n - 1 && state[actions][right + 1] > 0) {
                ++right;
            }
            ++actions;
            for (int j = left; j <= right; ++j) {
                --state[actions][j];
            }
            for (int j = 0; j < n; ++j) {
                if (j < left || j > right) {
                    state[actions][j] = state[actions - 1][j];
                }
            }
        }
    }

    cout << actions << endl;
    return 0;
}
