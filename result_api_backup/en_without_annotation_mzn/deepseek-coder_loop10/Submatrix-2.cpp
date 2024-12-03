#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

int main() {
    int N, M, R, C;
    cin >> N >> M >> R >> C;
    vector<vector<int>> a(N, vector<int>(M));
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < M; ++j) {
            cin >> a[i][j];
        }
    }

    vector<int> b(R), c(C);
    for (int i = 0; i < R; ++i) b[i] = i * (N - 1) / (R - 1);
    for (int i = 0; i < C; ++i) c[i] = i * (M - 1) / (C - 1);

    int score = 0;
    for (int i = 0; i < R - 1; ++i) {
        for (int j = 0; j < C; ++j) {
            score += abs(a[b[i]][c[j]] - a[b[i + 1]][c[j]]);
        }
    }
    for (int i = 0; i < R; ++i) {
        for (int j = 0; j < C - 1; ++j) {
            score += abs(a[b[i]][c[j]] - a[b[i]][c[j + 1]]);
        }
    }

    cout << "score=" << score << endl;
    return 0;
}