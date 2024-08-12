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

    vector<int> maxCoins(M + 1, M); // Initialize with the initial coins

    for (int day = 0; day < T; ++day) {
        vector<int> newCoins(maxCoins);
        for (int j = 0; j < N; ++j) {
            int price = prices[day][j];
            for (int coins = 0; coins <= M; ++coins) {
                if (maxCoins[coins] < coins) continue;
                int count = coins / price;
                if (count > 0) {
                    int profit = count * price;
                    newCoins[coins - (count * price) + profit] = max(newCoins[coins - (count * price) + profit], maxCoins[coins]);
                }
            }
        }
        maxCoins = newCoins;
    }

    int result = 0;
    for (int coins = 0; coins <= M; ++coins) {
        if (maxCoins[coins] > result) {
            result = maxCoins[coins];
        }
    }

    cout << result << endl;
    return 0;
}