#include <iostream>
#include <vector>
#include <cmath>
#include <climits>
using namespace std;

int N, M, R, C;
vector<vector<int>> a;
vector<int> b, c;

int computeScore(const vector<int>& b, const vector<int>& c, const vector<vector<int>>& a) {
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
    return score;
}

void solve(int idx, int currentScore, int& minScore) {
    if (idx == R + C) {
        int score = computeScore(b, c, a);
        if (score < minScore) {
            minScore = score;
        }
        return;
    }

    if (idx < R) {  // assign values to b
        for (int i = 1; i <= N; ++i) {
            if (idx == 0 || i > b[idx - 1]) {
                b[idx] = i;
                solve(idx + 1, currentScore, minScore);
            }
        }
    } else {  // assign values to c
        for (int j = 1; j <= M; ++j) {
            if (idx == R || j > c[idx - R - 1]) {
                c[idx - R] = j;
                solve(idx + 1, currentScore, minScore);
            }
        }
    }
}

int main() {
    cin >> N >> M >> R >> C;
    a = vector<vector<int>>(N, vector<int>(M));
    b = vector<int>(R);
    c = vector<int>(C);

    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < M; ++j) {
            cin >> a[i][j];
        }
    }

    int minScore = INT_MAX;
    solve(0, 0, minScore);
    cout << "score=" << minScore << endl;

    return 0;
}