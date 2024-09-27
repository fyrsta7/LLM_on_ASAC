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
    for (int i = 0; i < R; ++i) {
        b[i] = i + 1;
    }
    for (int i = 0; i < C; ++i) {
        c[i] = i + 1;
    }

    int minScore = INT_MAX;
    do {
        do {
            int score = 0;
            for (int i = 0; i < R - 1; ++i) {
                for (int j = 0; j < C; ++j) {
                    score += abs(a[b[i] - 1][c[j] - 1] - a[b[i + 1] - 1][c[j] - 1]);
                }
            }
            for (int i = 0; i < R; ++i) {
                for (int j = 0; j < C - 1; ++j) {
                    score += abs(a[b[i] - 1][c[j] - 1] - a[b[i] - 1][c[j + 1] - 1]);
                }
            }
            minScore = min(minScore, score);
        } while (next_permutation(c.begin(), c.end()));
    } while (next_permutation(b.begin(), b.end()));

    cout << "score=" << minScore << endl;
    return 0;
}