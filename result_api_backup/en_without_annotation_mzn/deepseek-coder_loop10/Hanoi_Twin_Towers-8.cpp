#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const int INF = 1000;
const int MAX_STEPS = 100;

void move(int from, int to, vector<vector<int>>& state) {
    int n = state[0].size() / 2;
    int top_from = state[from][0];
    state[from].erase(state[from].begin());
    state[to].insert(state[to].begin(), top_from);
}

int solve(int n) {
    vector<vector<int>> initial_state(3, vector<int>(2 * n, INF));
    for (int i = 0; i < n; ++i) {
        initial_state[0][2 * i] = initial_state[0][2 * i + 1] = i + 1;
    }

    vector<vector<vector<int>>> states(MAX_STEPS + 1, vector<vector<int>>(3, vector<int>(2 * n, INF)));
    states[0] = initial_state;

    vector<pair<int, int>> actions(MAX_STEPS);

    for (int steps = 1; steps <= MAX_STEPS; ++steps) {
        for (int from = 0; from < 3; ++from) {
            for (int to = 0; to < 3; ++to) {
                if (from == to) continue;
                if (states[steps - 1][from][0] == INF) continue;
                if (states[steps - 1][to][0] != INF && states[steps - 1][from][0] > states[steps - 1][to][0]) continue;

                states[steps] = states[steps - 1];
                move(from, to, states[steps]);
                actions[steps - 1] = {from + 1, to + 1};

                bool solved = true;
                for (int i = 0; i < n; ++i) {
                    if (states[steps][2][2 * i] != i + 1 || states[steps][2][2 * i + 1] != i + 1) {
                        solved = false;
                        break;
                    }
                }
                if (solved) return steps;
            }
        }
    }

    return MAX_STEPS;
}

int main() {
    int n;
    cin >> n;
    cout << solve(n) << endl;
    return 0;
}
