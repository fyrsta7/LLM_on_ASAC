#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const int INF = 1000;
const int MAX_STEPS = 100;

void move(int from, int to, vector<vector<int>>& state) {
    int n = state[0].size() / 2;
    int top_from = -1, top_to = -1;
    for (int i = 1; i <= 2 * n; ++i) {
        if (state[from - 1][i - 1] != INF) {
            top_from = i;
            break;
        }
    }
    for (int i = 1; i <= 2 * n; ++i) {
        if (state[to - 1][i - 1] != INF) {
            top_to = i;
            break;
        }
    }
    if (top_from == -1) return;
    if (top_to == -1 || state[from - 1][top_from - 1] < state[to - 1][top_to - 1]) {
        state[to - 1][top_to - 1] = state[from - 1][top_from - 1];
        state[from - 1][top_from - 1] = INF;
    }
}

int main() {
    int n;
    cin >> n;

    vector<vector<int>> initial_state(3, vector<int>(2 * n, INF));
    for (int i = 1; i <= n; ++i) {
        initial_state[0][2 * i - 2] = i;
        initial_state[0][2 * i - 1] = i;
    }

    vector<vector<vector<int>>> states(MAX_STEPS + 1, vector<vector<int>>(3, vector<int>(2 * n, INF)));
    states[0] = initial_state;

    vector<pair<int, int>> actions(MAX_STEPS);

    for (int step = 1; step <= MAX_STEPS; ++step) {
        for (int from = 1; from <= 3; ++from) {
            for (int to = 1; to <= 3; ++to) {
                if (from == to) continue;
                vector<vector<int>> new_state = states[step - 1];
                move(from, to, new_state);
                bool valid = true;
                for (int i = 1; i <= n; ++i) {
                    if (new_state[2][2 * i - 2] != i || new_state[2][2 * i - 1] != i) {
                        valid = false;
                        break;
                    }
                }
                if (valid) {
                    actions[step - 1] = {from, to};
                    states[step] = new_state;
                    cout << step << endl;
                    return 0;
                }
            }
        }
    }

    cout << MAX_STEPS << endl;
    return 0;
}
