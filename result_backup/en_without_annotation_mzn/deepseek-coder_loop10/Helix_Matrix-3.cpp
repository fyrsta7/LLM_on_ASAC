#include <iostream>
#include <vector>

using namespace std;

int main() {
    int N, I, J;
    cin >> N >> I >> J;

    vector<vector<int>> a(N + 2, vector<int>(N + 2, 0));
    vector<vector<int>> b(N + 1, vector<int>(N + 1, 0));
    vector<vector<int>> c(N + 1, vector<int>(N + 1, 0));

    vector<pair<int, int>> d = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};

    for (int i = 1; i <= N; ++i) {
        for (int j = 1; j <= N; ++j) {
            a[i][j] = (i - 1) * N + j;
        }
    }

    for (int i = 1; i <= N; ++i) {
        for (int j = 1; j <= N; ++j) {
            int dir = 0;
            for (int k = 0; k < 4; ++k) {
                int ni = i + d[k].first;
                int nj = j + d[k].second;
                if (ni >= 1 && ni <= N && nj >= 1 && nj <= N && a[ni][nj] == a[i][j] + 1) {
                    dir = k + 1;
                    break;
                }
            }
            b[i][j] = dir;
            c[i][j] = dir;
        }
    }

    cout << "ans=" << a[I][J] << endl;

    return 0;
}
