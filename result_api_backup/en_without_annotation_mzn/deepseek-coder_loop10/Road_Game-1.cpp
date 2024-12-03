#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    int n, m, p;
    cin >> n >> m >> p;

    vector<vector<int>> coins(n, vector<int>(m));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            cin >> coins[i][j];
        }
    }

    vector<int> cost(n);
    for (int i = 0; i < n; ++i) {
        cin >> cost[i];
    }

    vector<int> strategy(m, 0);
    vector<int> runtime(m, 0);
    vector<int> location(m, 0);
    int pointer = 0;
    int benefit = 0;

    for (int i = 0; i < m; ++i) {
        int max_benefit = INT_MIN;
        int best_strategy = 0;
        int best_runtime = 0;
        int best_location = 0;

        for (int s = 1; s <= n; ++s) {
            for (int r = 1; r <= p; ++r) {
                if (i + r > m) break;
                int current_benefit = 0;
                for (int j = 0; j < r; ++j) {
                    int loc = (s - 2 + j) % n + 1;
                    current_benefit += coins[loc - 1][i + j];
                }
                current_benefit -= cost[s - 1];
                if (current_benefit > max_benefit) {
                    max_benefit = current_benefit;
                    best_strategy = s;
                    best_runtime = r;
                    best_location = (s - 2) % n + 1;
                }
            }
        }

        if (max_benefit > 0) {
            strategy[pointer] = best_strategy;
            runtime[pointer] = best_runtime;
            for (int j = 0; j < best_runtime; ++j) {
                location[i + j] = (best_location + j - 1) % n + 1;
            }
            benefit += max_benefit;
            pointer++;
            i += best_runtime - 1;
        }
    }

    cout << benefit << endl;

    return 0;
}
