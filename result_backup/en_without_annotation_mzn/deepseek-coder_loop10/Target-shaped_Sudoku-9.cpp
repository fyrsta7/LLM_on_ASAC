#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const int N = 9;
const int score[N][N] = {
    {6, 6, 6, 6, 6, 6, 6, 6, 6},
    {6, 7, 7, 7, 7, 7, 7, 7, 6},
    {6, 7, 8, 8, 8, 8, 8, 7, 6},
    {6, 7, 8, 9, 9, 9, 8, 7, 6},
    {6, 7, 8, 9, 10, 9, 8, 7, 6},
    {6, 7, 8, 9, 9, 9, 8, 7, 6},
    {6, 7, 8, 8, 8, 8, 8, 7, 6},
    {6, 7, 7, 7, 7, 7, 7, 7, 6},
    {6, 6, 6, 6, 6, 6, 6, 6, 6}
};

vector<vector<int>> origin(N, vector<int>(N));
vector<vector<int>> sudoku(N, vector<int>(N));

bool isValid(int row, int col, int num) {
    for (int i = 0; i < N; ++i) {
        if (sudoku[row][i] == num || sudoku[i][col] == num) return false;
    }
    int startRow = row - row % 3;
    int startCol = col - col % 3;
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            if (sudoku[startRow + i][startCol + j] == num) return false;
        }
    }
    return true;
}

int calculateScore() {
    int totalScore = 0;
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            totalScore += score[i][j] * sudoku[i][j];
        }
    }
    return totalScore;
}

int solve(int row, int col) {
    if (row == N) return calculateScore();
    if (col == N) return solve(row + 1, 0);
    if (origin[row][col] != 0) return solve(row, col + 1);

    int maxScore = 0;
    for (int num = 1; num <= N; ++num) {
        if (isValid(row, col, num)) {
            sudoku[row][col] = num;
            maxScore = max(maxScore, solve(row, col + 1));
            sudoku[row][col] = 0;
        }
    }
    return maxScore;
}

int main() {
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            cin >> origin[i][j];
            sudoku[i][j] = origin[i][j];
        }
    }
    cout << solve(0, 0) << endl;
    return 0;
}