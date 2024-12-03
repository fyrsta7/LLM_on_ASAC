#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const int infty = 1000;
const int max_steps = 100;

void move(int from, int to, vector<vector<int>>& state) {
    int n = state[0].size() / 2;
    int top_from = state[from][0];
    state[from].erase(state[from].begin());
    state[to].insert(state[to].begin(), top_from);
}

int solve(int n) {
    vector<vector<int>> initial_state(3, vector<int>(2 * n, infty));
    for (int i = 0; i < n; ++i) {
        initial_state[0][2 * i] = initial_state[0][2 * i + 1] = i + 1;
    }

    vector<vector<vector<int>>> states(max_steps + 1, vector<vector<int>>(3, vector<int>(2 * n, infty)));
    states[0] = initial_state;

    vector<pair<int, int>> actions(max_steps);

    int steps = 0;
    while (steps < max_steps) {
        bool found = false;
        for (int from = 0; from < 3; ++from) {
            for (int to = 0; to < 3; ++to) {
                if (from == to) continue;
                if (states[steps][from][0] < states[steps][to][0]) {
                    states[steps + 1] = states[steps];
                    move(from, to, states[steps + 1]);
                    actions[steps] = {from + 1, to + 1};
                    ++steps;
                    found = true;
                    break;
                }
            }
            if (found) break;
        }
        if (!found) break;
    }

    return steps;
}

int main() {
    int n;
    cin >> n;
    cout << solve(n) << endl;
    return 0;
}
