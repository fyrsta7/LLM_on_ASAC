#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const int INF = 1000;
const int MAX_STEPS = 100;

struct State {
    vector<int> rods[3];
    State(int n) {
        rods[0] = vector<int>(2 * n, INF);
        rods[1] = vector<int>(2 * n, INF);
        rods[2] = vector<int>(2 * n, INF);
        for (int i = 0; i < n; ++i) {
            rods[0][2 * i] = rods[0][2 * i + 1] = i + 1;
        }
    }
    bool operator==(const State& other) const {
        return rods[0] == other.rods[0] && rods[1] == other.rods[1] && rods[2] == other.rods[2];
    }
    bool is_goal(int n) const {
        for (int i = 0; i < n; ++i) {
            if (rods[2][2 * i] != i + 1 || rods[2][2 * i + 1] != i + 1) return false;
        }
        return true;
    }
    void move(int from, int to) {
        int disk = rods[from].back();
        rods[from].pop_back();
        rods[to].push_back(disk);
    }
};

int hanoi(int n) {
    State initial(n);
    vector<State> states = {initial};
    vector<pair<int, int>> actions;
    int steps = 0;

    while (steps < MAX_STEPS) {
        State current = states.back();
        if (current.is_goal(n)) break;

        bool moved = false;
        for (int from = 0; from < 3; ++from) {
            for (int to = 0; to < 3; ++to) {
                if (from == to) continue;
                if (current.rods[from].empty() || (!current.rods[to].empty() && current.rods[from].back() > current.rods[to].back())) continue;

                State next = current;
                next.move(from, to);
                if (find(states.begin(), states.end(), next) == states.end()) {
                    states.push_back(next);
                    actions.emplace_back(from, to);
                    moved = true;
                    break;
                }
            }
            if (moved) break;
        }
        if (!moved) break;
        ++steps;
    }

    return steps;
}

int main() {
    int n;
    cin >> n;
    cout << hanoi(n) << endl;
    return 0;
}
