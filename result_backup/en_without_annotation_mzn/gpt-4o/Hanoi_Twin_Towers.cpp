#include <iostream>
#include <vector>
#include <limits.h>

using namespace std;

const int INFTY = 1000;
const int MAX_STEPS = 100;

void move(int from, int to, vector<vector<int>>& before, vector<vector<int>>& after) {
    after = before;
    for (int i = 0; i < 2 * after[0].size(); ++i) {
        if (i < 2 * after[0].size() - 1) after[from][i] = before[from][i + 1];
        else after[from][i] = INFTY;
    }
    for (int i = 2 * after[0].size() - 1; i > 0; --i) {
        after[to][i] = before[to][i - 1];
    }
    after[to][0] = before[from][0];
}

void solve(int n) {
    vector<vector<int>> column(3, vector<int>(2 * n, INFTY));
    for (int i = 0; i < n; i++) {
        column[0][2 * i] = column[0][2 * i + 1] = i + 1;
    }
    
    vector<vector<vector<int>>> state(MAX_STEPS + 1, vector<vector<int>>(3, vector<int>(2 * n, INFTY)));
    state[0] = column;
    vector<int> steps(MAX_STEPS + 1, INT_MAX);
    steps[0] = 0;
    vector<vector<int>> action(MAX_STEPS + 1, vector<int>(2, 1));
    
    for (int step = 0; step < MAX_STEPS; ++step) {
        for (int from = 0; from < 3; ++from) {
            for (int to = 0; to < 3; ++to) {
                if (from != to) {
                    vector<vector<int>> next_state;
                    move(from, to, state[step], next_state);
                    bool valid = true;
                    for (int i = 1; i < 2 * n; ++i) {
                        if (next_state[from][i] < next_state[from][i - 1] || next_state[to][i] < next_state[to][i - 1]) {
                            valid = false;
                            break;
                        }
                    }
                    if (valid) {
                        state[step + 1] = next_state;
                        action[step] = {from + 1, to + 1};
                        steps[step + 1] = step + 1;
                        
                        bool goal_state = true;
                        for (int i = 0; i < n; ++i) {
                            if (state[step + 1][2][2 * i] != i + 1 || state[step + 1][2][2 * i + 1] != i + 1) {
                                goal_state = false;
                                break;
                            }
                        }
                        if (goal_state) {
                            cout << step + 1 << "\n";
                            return;
                        }
                    }
                }
            }
        }
    }
}

int main() {
    int n;
    cin >> n;
    solve(n);
    return 0;
}