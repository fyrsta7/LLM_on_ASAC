#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

int N, M, R, C;
vector<vector<int>> a;
vector<int> b, c;

int calculateScore() {
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
    return score;
}

int main() {
    cin >> N >> M >> R >> C;
    a.resize(N, vector<int>(M));
    b.resize(R);
    c.resize(C);

    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < M; ++j) {
            cin >> a[i][j];
        }
    }

    for (int i = 0; i < R; ++i) {
        b[i] = i + 1;
    }
    for (int i = 0; i < C; ++i) {
        c[i] = i + 1;
    }

    int minScore = calculateScore();

    while (next_permutation(b.begin(), b.end())) {
        while (next_permutation(c.begin(), c.end())) {
            minScore = min(minScore, calculateScore());
        }
    }

    cout << "score=" << minScore << endl;

    return 0;
}