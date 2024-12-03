#include <iostream>
#include <vector>

using namespace std;

const int directions[4][2] = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};

int main() {
    int N, I, J;
    cin >> N >> I >> J;

    vector<vector<int>> a(N + 2, vector<int>(N + 2, 0));
    vector<vector<int>> b(N + 1, vector<int>(N + 1, 0));
    vector<vector<int>> c(N + 1, vector<int>(N + 1, 0));

    for (int i = 1; i <= N; ++i) {
        for (int j = 1; j <= N; ++j) {
            a[i][j] = (i - 1) * N + j;
            c[i][j] = (i == 1 && j == 1) ? 1 : ((j == 1) ? 4 : (c[i][j - 1] % 4 + 1));
        }
    }

    for (int i = 1; i <= N; ++i) {
        for (int j = 1; j <= N; ++j) {
            int ni = i + directions[c[i][j] - 1][0];
            int nj = j + directions[c[i][j] - 1][1];
            if (a[ni][nj] < a[i][j]) {
                b[i][j] = c[i][j];
            } else {
                b[i][j] = (c[i][j] % 4) + 1;
            }
        }
    }

    cout << "ans=" << a[I][J] << endl;

    return 0;
}
