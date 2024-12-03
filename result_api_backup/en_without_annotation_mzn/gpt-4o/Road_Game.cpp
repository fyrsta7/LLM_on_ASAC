#include <iostream>
#include <vector>
#include <climits>
using namespace std;

int main() {
    int n, m, p;
    cin >> n >> m >> p;
    vector<vector<int>> coins(n, vector<int>(m));
    vector<int> cost(n);
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < m; ++j)
            cin >> coins[i][j];
    for (int i = 0; i < n; ++i)
        cin >> cost[i];

    vector<int> strategy(m, 0), runtime(m, 0), location(m, 0);
    int pointer = 0;
    int max_benefit = INT_MIN;

    auto calculate_benefit = [&]() {
        int sum_coins = 0, sum_cost = 0;
        for (int i = 0; i < m; ++i) {
            int loc = location[i];
            if (loc > 0)
                sum_coins += coins[loc - 1][i];
        }
        for (int i = 0; i < pointer; ++i) {
            if (strategy[i] > 0)
                sum_cost += cost[strategy[i] - 1];
        }
        return sum_coins - sum_cost;
    };

    auto generate_combinations = [&](int strategy_index, int strategy_pos) {
        if (strategy_index >= m)
            return;

        for (int st = 1; st <= n; ++st) {
            strategy[strategy_index] = st;
            for (int run = 1; run <= p; ++run) {
                runtime[strategy_index] = run;
                int sum_runtime = 0;
                for (int i = 0; i <= strategy_index; ++i)
                    sum_runtime += runtime[i];
                if (sum_runtime > m)
                    break;

                for (int loc = 0; loc < run; ++loc) {
                    location[strategy_pos + loc] = (st - 2 + loc + 1) % n + 1;
                }
                pointer = strategy_index + 1;
                int benefit = calculate_benefit();
                max_benefit = max(max_benefit, benefit);

                generate_combinations(strategy_index + 1, strategy_pos + run);
            }
        }
    };

    generate_combinations(0, 0);

    cout << max_benefit << endl;
    return 0;
}