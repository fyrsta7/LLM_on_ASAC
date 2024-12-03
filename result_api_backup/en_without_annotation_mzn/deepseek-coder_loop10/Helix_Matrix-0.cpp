#include <iostream>
#include <vector>

using namespace std;

int main() {
    int N, I, J;
    cin >> N >> I >> J;

    vector<vector<int>> a(N + 2, vector<int>(N + 2, 0));
    vector<vector<int>> b(N + 2, vector<int>(N + 2, 0));
    vector<vector<int>> c(N + 2, vector<int>(N + 2, 0));

    vector<pair<int, int>> d = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};

    for (int i = 1; i <= N; ++i) {
        for (int j = 1; j <= N; ++j) {
            a[i][j] = (i - 1) * N + j;
            c[i][j] = (i == 1 && j == 1) ? 1 : ((j == 1) ? 2 : ((i == N) ? 3 : 0));
            b[i][j] = (i == 1 && j == 1) ? 1 : ((j == 1) ? 2 : ((i == N) ? 3 : 0));
        }
    }

    cout << "ans=" << a[I][J] << endl;

    return 0;
}