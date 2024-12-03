#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const int INF = 1000;
const int MAX_STEPS = 100;

struct State {
    vector<int> rods[3];
    State(int n) {
        rods[0].resize(2 * n, INF);
        rods[1].resize(2 * n, INF);
        rods[2].resize(2 * n, INF);
        for (int i = 0; i < n; ++i) {
            rods[0][2 * i] = rods[0][2 * i + 1] = i + 1;
        }
    }
    bool isGoal(int n) const {
        for (int i = 0; i < n; ++i) {
            if (rods[2][2 * i] != i + 1 || rods[2][2 * i + 1] != i + 1) return false;
        }
        for (int i = 0; i < 2 * n; ++i) {
            if (rods[0][i] != INF || rods[1][i] != INF) return false;
        }
        return true;
    }
    void move(int from, int to) {
        int top = rods[from][0];
        rods[from].erase(rods[from].begin());
        rods[to].insert(rods[to].begin(), top);
    }
};

int solve(int n) {
    vector<State> states(MAX_STEPS + 1, State(n));
    vector<pair<int, int>> actions(MAX_STEPS);
    int steps = 0;

    while (steps < MAX_STEPS) {
        if (states[steps].isGoal(n)) break;
        bool moved = false;
        for (int from = 0; from < 3; ++from) {
            for (int to = 0; to < 3; ++to) {
                if (from == to) continue;
                if (states[steps].rods[from][0] < states[steps].rods[to][0]) {
                    states[steps + 1] = states[steps];
                    states[steps + 1].move(from, to);
                    actions[steps] = {from + 1, to + 1};
                    ++steps;
                    moved = true;
                    break;
                }
            }
            if (moved) break;
        }
        if (!moved) break;
    }

    return steps;
}

int main() {
    int n;
    cin >> n;
    cout << solve(n) << endl;
    return 0;
}
