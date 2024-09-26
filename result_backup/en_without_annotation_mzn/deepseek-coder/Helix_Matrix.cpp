#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    int N, I, J;
    cin >> N >> I >> J;

    vector<vector<int>> a(N + 2, vector<int>(N + 2, 0));
    vector<vector<int>> b(N + 1, vector<int>(N + 1, 0));
    vector<vector<int>> c(N + 1, vector<int>(N + 1, 0));

    vector<pair<int, int>> directions = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};

    for (int i = 1; i <= N; ++i) {
        for (int j = 1; j <= N; ++j) {
            a[i][j] = (i - 1) * N + j;
        }
    }

    for (int i = 1; i <= N; ++i) {
        for (int j = 1; j <= N; ++j) {
            c[i][j] = 1;
        }
    }

    for (int i = 1; i <= N; ++i) {
        for (int j = 1; j <= N; ++j) {
            if (a[i][j] == N * N) continue;
            int min_dir = -1, min_val = N * N + 1;
            for (int k = 0; k < 4; ++k) {
                int ni = i + directions[k].first;
                int nj = j + directions[k].second;
                if (a[ni][nj] < a[i][j] && a[ni][nj] < min_val) {
                    min_val = a[ni][nj];
                    min_dir = k;
                }
            }
            b[i][j] = (min_dir + 1) % 4 + 1;
        }
    }

    cout << "ans=" << a[I][J] << endl;

    return 0;
}
