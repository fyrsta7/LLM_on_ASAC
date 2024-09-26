#include <iostream>
#include <vector>
#include <climits>

using namespace std;

int calculateScore(const vector<vector<int>>& submatrix, int r, int c) {
    int score = 0;
    for (int i = 0; i < r; ++i) {
        for (int j = 0; j < c; ++j) {
            if (i < r - 1) {
                score += abs(submatrix[i][j] - submatrix[i + 1][j]);
            }
            if (j < c - 1) {
                score += abs(submatrix[i][j] - submatrix[i][j + 1]);
            }
        }
    }
    return score;
}

int main() {
    int n, m, r, c;
    cin >> n >> m >> r >> c;
    vector<vector<int>> matrix(n, vector<int>(m));

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            cin >> matrix[i][j];
        }
    }

    int minScore = INT_MAX;

    for (int i = 0; i <= n - r; ++i) {
        for (int j = 0; j <= m - c; ++j) {
            vector<vector<int>> submatrix(r, vector<int>(c));
            for (int x = 0; x < r; ++x) {
                for (int y = 0; y < c; ++y) {
                    submatrix[x][y] = matrix[i + x][j + y];
                }
            }
            int score = calculateScore(submatrix, r, c);
            minScore = min(minScore, score);
        }
    }

    cout << minScore << endl;
    return 0;
}