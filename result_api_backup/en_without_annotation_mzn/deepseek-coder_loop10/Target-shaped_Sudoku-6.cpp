#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>

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

int origin[N][N];
int sudoku[N][N];
bool row[N][N + 1], col[N][N + 1], block[N / 3][N / 3][N + 1];

int total_score = 0;

void dfs(int x, int y) {
    if (x == N) {
        int current_score = 0;
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < N; ++j) {
                current_score += score[i][j] * sudoku[i][j];
            }
        }
        total_score = max(total_score, current_score);
        return;
    }

    if (y == N) {
        dfs(x + 1, 0);
        return;
    }

    if (sudoku[x][y] != 0) {
        dfs(x, y + 1);
        return;
    }

    for (int num = 1; num <= N; ++num) {
        if (!row[x][num] && !col[y][num] && !block[x / 3][y / 3][num]) {
            row[x][num] = col[y][num] = block[x / 3][y / 3][num] = true;
            sudoku[x][y] = num;
            dfs(x, y + 1);
            sudoku[x][y] = 0;
            row[x][num] = col[y][num] = block[x / 3][y / 3][num] = false;
        }
    }
}

int main() {
    memset(row, false, sizeof(row));
    memset(col, false, sizeof(col));
    memset(block, false, sizeof(block));

    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            cin >> origin[i][j];
            sudoku[i][j] = origin[i][j];
            if (sudoku[i][j] != 0) {
                row[i][sudoku[i][j]] = true;
                col[j][sudoku[i][j]] = true;
                block[i / 3][j / 3][sudoku[i][j]] = true;
            }
        }
    }

    dfs(0, 0);
    cout << total_score << endl;

    return 0;
}