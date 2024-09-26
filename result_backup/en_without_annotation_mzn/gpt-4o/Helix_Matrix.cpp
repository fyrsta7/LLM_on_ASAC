#include <iostream>
#include <vector>
using namespace std;

int N, I, J;
const int d[5][2] = {{0, 0}, {0, 1}, {1, 0}, {0, -1}, {-1, 0}};

void solve() {
    vector<vector<int>> a(N + 2, vector<int>(N + 2, 0));
    vector<vector<int>> b(N + 1, vector<int>(N + 1, 0));
    vector<vector<int>> c(N + 1, vector<int>(N + 1, 0));

    a[1][1] = 1;
    c[1][1] = 1;

    for (int i = 1; i <= N; ++i) {
        for (int j = 1; j <= N; ++j) {
            if (i == 1 && j == 1) continue;
            int minVal = N * N + 1;
            int dir = 0;
            for (int k = 1; k <= 4; ++k) {
                int ni = i - d[k][0];
                int nj = j - d[k][1];
                if (ni >= 1 && ni <= N && nj >= 1 && nj <= N && a[ni][nj] > 0 && a[ni][nj] < minVal) {
                    minVal = a[ni][nj];
                    dir = k;
                }
            }
            a[i][j] = minVal + 1;
            c[i][j] = dir;
        }
    }

    for (int i = 1; i <= N; ++i) {
        for (int j = 1; j <= N; ++j) {
            if (a[i][j] == N * N) continue;
            int ni = i + d[c[i][j]][0];
            int nj = j + d[c[i][j]][1];
            if (a[ni][nj] < a[i][j]) {
                b[i][j] = (c[i][j] % 4) + 1;
            } else {
                b[i][j] = c[i][j];
            }
        }
    }

    for (int i = 1; i <= N; ++i) {
        for (int j = 1; j <= N; ++j) {
            if (a[i][j] == N * N) continue;
            int ni = i + d[b[i][j]][0];
            int nj = j + d[b[i][j]][1];
            if (a[ni][nj] != a[i][j] + 1) {
                a[ni][nj] = a[i][j] + 1;
                c[ni][nj] = b[i][j];
            }
        }
    }

    cout << "ans=" << a[I][J] << endl;
}

int main() {
    cin >> N >> I >> J;
    solve();
    return 0;
}