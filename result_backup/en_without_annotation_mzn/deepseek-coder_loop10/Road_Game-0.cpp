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

    int maxBenefit = 0;

    for (int strategy = 1; strategy <= n; ++strategy) {
        int totalRuntime = 0;
        int currentBenefit = 0;

        for (int i = 0; i < m; ++i) {
            int location = (strategy - 2 + i) % n + 1;
            currentBenefit += coins[location - 1][i];
            totalRuntime++;

            if (totalRuntime == m) {
                currentBenefit -= cost[strategy - 1];
                break;
            }
        }

        maxBenefit = max(maxBenefit, currentBenefit);
    }

    cout << maxBenefit << endl;

    return 0;
}
