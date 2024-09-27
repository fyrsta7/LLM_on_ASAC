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
            top_from = i - 1;
            break;
        }
    }

    for (int i = 1; i <= 2 * n; ++i) {
        if (state[to - 1][i - 1] != INF) {
            top_to = i - 1;
            break;
        }
    }

    if (top_from == -1) return;
    if (top_to == -1) top_to = 2 * n;

    swap(state[from - 1][top_from], state[to - 1][top_to]);
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

    int steps = 0;
    while (steps < MAX_STEPS) {
        bool found = false;
        for (int from = 1; from <= 3 && !found; ++from) {
            for (int to = 1; to <= 3 && !found; ++to) {
                if (from == to) continue;
                vector<vector<int>> new_state = states[steps];
                move(from, to, new_state);
                bool valid = true;
                for (int i = 1; i <= n && valid; ++i) {
                    if (new_state[2][2 * i - 2] != i || new_state[2][2 * i - 1] != i) {
                        valid = false;
                    }
                }
                for (int i = 0; i < 2 * n && valid; ++i) {
                    if (new_state[0][i] != INF || new_state[1][i] != INF) {
                        valid = false;
                    }
                }
                if (valid) {
                    actions[steps] = {from, to};
                    states[steps + 1] = new_state;
                    found = true;
                    steps++;
                }
            }
        }
        if (!found) break;
    }

    cout << steps << endl;

    return 0;
}
