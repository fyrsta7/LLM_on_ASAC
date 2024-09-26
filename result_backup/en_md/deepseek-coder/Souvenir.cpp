#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    int T, N, M;
    cin >> T >> N >> M;
    vector<vector<int>> prices(T, vector<int>(N));
    for (int i = 0; i < T; ++i) {
        for (int j = 0; j < N; ++j) {
            cin >> prices[i][j];
        }
    }

    for (int day = 0; day < T - 1; ++day) {
        vector<int> profit(N, 0);
        for (int j = 0; j < N; ++j) {
            profit[j] = prices[day + 1][j] - prices[day][j];
        }

        while (true) {
            int max_profit = 0, max_index = -1;
            for (int j = 0; j < N; ++j) {
                if (profit[j] > max_profit && prices[day][j] <= M) {
                    max_profit = profit[j];
                    max_index = j;
                }
            }

            if (max_index == -1) break;

            int quantity = M / prices[day][max_index];
            M -= quantity * prices[day][max_index];
            M += quantity * prices[day + 1][max_index];
            profit[max_index] = 0;
        }
    }

    cout << M << endl;
    return 0;
}
