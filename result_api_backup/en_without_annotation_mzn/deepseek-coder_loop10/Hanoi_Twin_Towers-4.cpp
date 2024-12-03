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
    if (top_to == -1) top_to = 2 * n + 1;
    
    swap(state[from - 1][top_from - 1], state[to - 1][top_to - 2]);
}

int solve(int n) {
    vector<vector<int>> initial_state(3, vector<int>(2 * n, INF));
    for (int i = 1; i <= n; ++i) {
        initial_state[0][2 * i - 2] = initial_state[0][2 * i - 1] = i;
    }
    
    vector<vector<vector<int>>> states(MAX_STEPS + 1, vector<vector<int>>(3, vector<int>(2 * n, INF)));
    states[0] = initial_state;
    
    for (int steps = 1; steps <= MAX_STEPS; ++steps) {
        for (int from = 1; from <= 3; ++from) {
            for (int to = 1; to <= 3; ++to) {
                if (from == to) continue;
                
                states[steps] = states[steps - 1];
                move(from, to, states[steps]);
                
                bool valid = true;
                for (int i = 0; i < 2 * n; ++i) {
                    if (states[steps][0][i] != INF || states[steps][1][i] != INF) {
                        valid = false;
                        break;
                    }
                }
                
                for (int i = 1; i <= n; ++i) {
                    if (states[steps][2][2 * i - 2] != i || states[steps][2][2 * i - 1] != i) {
                        valid = false;
                        break;
                    }
                }
                
                if (valid) return steps;
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
