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
    if (top_to == -1) top_to = 0;
    swap(state[from - 1][top_from - 1], state[to - 1][top_to]);
}

int main() {
    int n;
    cin >> n;

    vector<vector<int>> initial_state(3, vector<int>(2 * n, INF));
    for (int i = 1; i <= n; ++i) {
        initial_state[0][2 * i - 2] = i;
        initial_state[0][2 * i - 1] = i;
    }

    vector<vector<vector<int>>> state(MAX_STEPS + 1, vector<vector<int>>(3, vector<int>(2 * n, INF)));
    state[0] = initial_state;

    vector<pair<int, int>> actions;
    int steps = 0;

    while (steps < MAX_STEPS) {
        bool moved = false;
        for (int from = 1; from <= 3; ++from) {
            for (int to = 1; to <= 3; ++to) {
                if (from == to) continue;
                vector<vector<int>> new_state = state[steps];
                move(from, to, new_state);
                bool valid = true;
                for (int i = 0; i < 2 * n - 1; ++i) {
                    if (new_state[from - 1][i] > new_state[from - 1][i + 1]) {
                        valid = false;
                        break;
                    }
                }
                if (valid) {
                    state[steps + 1] = new_state;
                    actions.emplace_back(from, to);
                    ++steps;
                    moved = true;
                    break;
                }
            }
            if (moved) break;
        }
        if (!moved) break;
    }

    cout << steps << endl;
    return 0;
}
