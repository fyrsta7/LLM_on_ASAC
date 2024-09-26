#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    int T, N, M;
    cin >> T >> N >> M;
    vector<vector<int>> P(T, vector<int>(N));
    for (int i = 0; i < T; ++i)
        for (int j = 0; j < N; ++j)
            cin >> P[i][j];

    vector<vector<int>> souvenir(T + 1, vector<int>(N, 0));
    vector<int> coin(T + 1, 0);
    coin[0] = M;

    for (int i = 1; i <= T; ++i) {
        vector<int> best_so_far(N, 0);
        for (int j = 0; j < N; ++j) {
            int max_buys = coin[i - 1] / P[i - 1][j];
            for (int b = 0; b <= max_buys; ++b) {
                int remaining_coins = coin[i - 1] - b * P[i - 1][j];
                if (remaining_coins < 0) continue;

                souvenir[i][j] = souvenir[i - 1][j] + b; // Update souvenirs with buys
                coin[i] = max(coin[i], remaining_coins); // Update max coins
            }
            best_so_far[j] = coin[i];
        }
        coin[i] = *max_element(best_so_far.begin(), best_so_far.end());
    }

    cout << coin[T] << endl;
    return 0;
}