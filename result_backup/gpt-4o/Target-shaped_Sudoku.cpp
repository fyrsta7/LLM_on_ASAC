#include <iostream>

using namespace std;

int board[9][9];
int row[9][10];
int col[9][10];
int block[3][3][10];
int scores[9][9] = {
    {6, 6, 6, 6, 7, 6, 6, 6, 6},
    {6, 7, 7, 7, 7, 7, 7, 7, 6},
    {6, 7, 8, 8, 8, 8, 8, 7, 6},
    {6, 7, 8, 9, 9, 9, 8, 7, 6},
    {7, 7, 8, 9, 10, 9, 8, 7, 7},
    {6, 7, 8, 9, 9, 9, 8, 7, 6},
    {6, 7, 8, 8, 8, 8, 8, 7, 6},
    {6, 7, 7, 7, 7, 7, 7, 7, 6},
    {6, 6, 6, 6, 7, 6, 6, 6, 6}
};

bool solve(int r, int c) {
    if (r == 9) return true;
    if (c == 9) return solve(r + 1, 0);
    if (board[r][c] != 0) return solve(r, c + 1);

    for (int num = 1; num <= 9; num++) {
        if (!row[r][num] && !col[c][num] && !block[r / 3][c / 3][num]) {
            row[r][num] = col[c][num] = block[r / 3][c / 3][num] = 1;
            board[r][c] = num;

            if (solve(r, c + 1)) return true;

            board[r][c] = 0;
            row[r][num] = col[c][num] = block[r / 3][c / 3][num] = 0;
        }
    }
    return false;
}

int main() {
    for (int i = 0; i < 9; i++)
        for (int j = 0; j < 9; j++) {
            cin >> board[i][j];
            if (board[i][j] != 0) {
                int num = board[i][j];
                row[i][num] = 1;
                col[j][num] = 1;
                block[i / 3][j / 3][num] = 1;
            }
        }

    if (solve(0, 0)) {
        int total_score = 0;
        for (int i = 0; i < 9; i++)
            for (int j = 0; j < 9; j++)
                total_score += board[i][j] * scores[i][j];
        cout << total_score << endl;
    } else {
        cout << -1 << endl;
    }

    return 0;
}