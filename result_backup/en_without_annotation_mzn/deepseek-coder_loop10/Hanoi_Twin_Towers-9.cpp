#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const int INF = 1000;
const int MAX_STEPS = 100;

struct State {
    vector<vector<int>> columns;
    State(int n) : columns(3, vector<int>(2 * n, INF)) {}
};

bool move(int from, int to, const State& before, State& after) {
    for (int i = 0; i < 3; ++i) {
        if (i != from && i != to) {
            after.columns[i] = before.columns[i];
        }
    }
    for (int i = 0; i < 2 * n - 1; ++i) {
        after.columns[from][i] = before.columns[from][i + 1];
    }
    after.columns[from][2 * n - 1] = INF;
    for (int i = 1; i < 2 * n; ++i) {
        after.columns[to][i] = before.columns[to][i - 1];
    }
    after.columns[to][0] = before.columns[from][0];
    return true;
}

int hanoi(int n) {
    State initial(n);
    for (int i = 1; i <= n; ++i) {
        initial.columns[0][2 * (i - 1)] = i;
        initial.columns[0][2 * (i - 1) + 1] = i;
    }

    vector<State> states(MAX_STEPS + 1, State(n));
    states[0] = initial;

    vector<pair<int, int>> actions(MAX_STEPS);

    for (int steps = 1; steps <= MAX_STEPS; ++steps) {
        for (int from = 1; from <= 3; ++from) {
            for (int to = 1; to <= 3; ++to) {
                if (from == to) continue;
                State next = states[steps - 1];
                if (move(from - 1, to - 1, states[steps - 1], next)) {
                    states[steps] = next;
                    actions[steps - 1] = {from, to};
                    bool solved = true;
                    for (int i = 1; i <= n; ++i) {
                        if (next.columns[2][2 * (i - 1)] != i || next.columns[2][2 * (i - 1) + 1] != i) {
                            solved = false;
                            break;
                        }
                    }
                    if (solved) {
                        return steps;
                    }
                }
            }
        }
    }
    return MAX_STEPS;
}

int main() {
    int n;
    cin >> n;
    cout << hanoi(n) << endl;
    return 0;
}
