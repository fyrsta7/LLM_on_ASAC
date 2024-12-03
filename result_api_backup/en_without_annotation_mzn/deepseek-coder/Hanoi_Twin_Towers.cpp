#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    int n;
    cin >> n;

    int max_steps = 100;
    int infty = 1000;

    vector<vector<int>> column(3, vector<int>(2 * n, infty));
    for (int i = 0; i < n; ++i) {
        column[0][2 * i] = column[0][2 * i + 1] = i + 1;
    }

    vector<vector<vector<int>>> state(max_steps + 1, vector<vector<int>>(3, vector<int>(2 * n, infty)));
    state[0] = column;

    vector<pair<int, int>> actions;

    auto move = [&](int from, int to, int step) {
        state[step + 1] = state[step];
        int disk = state[step][from][0];
        for (int i = 0; i < 2 * n - 1; ++i) {
            state[step + 1][from][i] = state[step][from][i + 1];
        }
        state[step + 1][from][2 * n - 1] = infty;
        for (int i = 2 * n - 1; i > 0; --i) {
            state[step + 1][to][i] = state[step][to][i - 1];
        }
        state[step + 1][to][0] = disk;
    };

    int steps = 0;
    while (steps < max_steps) {
        bool moved = false;
        for (int from = 0; from < 3; ++from) {
            for (int to = 0; to < 3; ++to) {
                if (from != to && state[steps][from][0] < state[steps][to][0]) {
                    move(from, to, steps);
                    actions.emplace_back(from + 1, to + 1);
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
    for (const auto& action : actions) {
        cout << action.first << " " << action.second << endl;
    }

    return 0;
}
