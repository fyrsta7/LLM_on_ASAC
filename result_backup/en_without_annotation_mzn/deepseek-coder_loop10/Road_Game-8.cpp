#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    int n, m, p;
    cin >> n >> m >> p;

    vector<vector<int>> coins(n, vector<int>(m));
    vector<int> cost(n);

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            cin >> coins[i][j];
        }
    }

    for (int i = 0; i < n; ++i) {
        cin >> cost[i];
    }

    vector<int> strategy(m, 0);
    vector<int> runtime(m, 0);
    vector<int> location(m, 0);

    int max_benefit = INT_MIN;

    for (int pointer = 1; pointer <= m; ++pointer) {
        for (int i = 0; i < pointer; ++i) {
            strategy[i] = i + 1;
            runtime[i] = 1;
            location[i] = (strategy[i] - 2 + runtime[i]) % n + 1;
        }

        do {
            int total_runtime = 0;
            for (int i = 0; i < pointer; ++i) {
                total_runtime += runtime[i];
            }

            if (total_runtime == m) {
                int benefit = 0;
                for (int i = 0; i < m; ++i) {
                    benefit += coins[location[i] - 1][i];
                }
                for (int i = 0; i < pointer; ++i) {
                    benefit -= cost[strategy[i] - 1];
                }

                max_benefit = max(max_benefit, benefit);
            }
        } while (next_permutation(strategy.begin(), strategy.begin() + pointer));
    }

    cout << max_benefit << endl;

    return 0;
}