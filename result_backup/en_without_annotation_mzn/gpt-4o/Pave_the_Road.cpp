#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    int n;
    cin >> n;
    vector<int> d(n);
    for (int i = 0; i < n; i++) {
        cin >> d[i];
    }

    int max_action = n * *max_element(d.begin(), d.end());
    vector<vector<int>> state(max_action + 1, vector<int>(n));
    vector<pair<int, int>> left_right(max_action + 1);
    state[0] = d;

    int actions = 0;
    bool completed = false;

    while (!completed && actions < max_action) {
        actions++;
        bool progress = false;
        for (int left = 0; left < n && !progress; left++) {
            for (int right = left; right < n && !progress; right++) {
                bool valid = true;
                for (int i = left; i <= right; i++) {
                    if (state[actions - 1][i] == 0) {
                        valid = false;
                        break;
                    }
                }
                if (valid) {
                    left_right[actions] = {left, right};
                    state[actions] = state[actions - 1];
                    for (int i = left; i <= right; i++) {
                        state[actions][i]--;
                    }
                    progress = true;
                }
            }
        }
        completed = all_of(state[actions].begin(), state[actions].end(), [](int x) { return x == 0; });
    }

    cout << actions << endl;
    return 0;
}