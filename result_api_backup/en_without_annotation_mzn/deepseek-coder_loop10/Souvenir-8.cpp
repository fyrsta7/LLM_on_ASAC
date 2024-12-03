#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    int T, N, M;
    cin >> T >> N >> M;
    vector<vector<int>> P(T + 1, vector<int>(N + 1));
    for (int i = 1; i <= T; ++i) {
        for (int j = 1; j <= N; ++j) {
            cin >> P[i][j];
        }
    }

    vector<int> coin(T + 1, 0);
    vector<vector<int>> souvenir(T + 1, vector<int>(N + 1, 0));
    vector<vector<int>> buy(T + 1, vector<int>(N + 1, 0));

    coin[0] = M;

    for (int i = 1; i <= T; ++i) {
        for (int j = 1; j <= N; ++j) {
            for (int k = 0; k <= coin[i - 1] / P[i][j]; ++k) {
                int new_coin = coin[i - 1] - k * P[i][j];
                int new_souvenir = souvenir[i - 1][j] + k;
                if (new_coin > coin[i]) {
                    coin[i] = new_coin;
                    for (int l = 1; l <= N; ++l) {
                        souvenir[i][l] = souvenir[i - 1][l];
                    }
                    souvenir[i][j] = new_souvenir;
                }
            }
        }
    }

    cout << coin[T] << endl;

    return 0;
}