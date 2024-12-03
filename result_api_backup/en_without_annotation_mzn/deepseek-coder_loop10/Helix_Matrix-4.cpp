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
            int next_i = i + d[b[i][j] - 1].first;
            int next_j = j + d[b[i][j] - 1].second;
            if (a[next_i][next_j] == a[i][j] + 1) {
                c[next_i][next_j] = b[i][j];
            } else {
                c[next_i][next_j] = (b[i][j] % 4) + 1;
            }
        }
    }

    cout << "ans=" << a[I][J] << endl;

    return 0;
}