#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

const int N = 9;
int board[N][N];
int score[N][N] = {
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

bool isValid(vector<vector<int>>& sudoku, int row, int col, int num) {
    for (int x = 0; x < N; x++)
        if (sudoku[row][x] == num || sudoku[x][col] == num)
            return false;

    int startRow = row - row % 3, startCol = col - col % 3;
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            if (sudoku[i + startRow][j + startCol] == num)
                return false;

    return true;
}

bool solveSudoku(vector<vector<int>>& sudoku) {
    int row = -1, col = -1;
    bool isEmpty = false;
    for (int i = 0; i < N && !isEmpty; i++) {
        for (int j = 0; j < N && !isEmpty; j++) {
            if (sudoku[i][j] == 0) {
                row = i;
                col = j;
                isEmpty = true;
            }
        }
    }

    if (!isEmpty)
        return true;

    for (int num = 1; num <= 9; num++) {
        if (isValid(sudoku, row, col, num)) {
            sudoku[row][col] = num;
            if (solveSudoku(sudoku))
                return true;
            sudoku[row][col] = 0;
        }
    }

    return false;
}

int main() {
    vector<vector<int>> sudoku(N, vector<int>(N));
    
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            cin >> sudoku[i][j];

    solveSudoku(sudoku);

    int total_score = 0;
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            total_score += sudoku[i][j] * score[i][j];

    cout << total_score << endl;

    return 0;
}