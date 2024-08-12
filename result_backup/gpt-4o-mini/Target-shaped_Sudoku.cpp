#include <iostream>
#include <vector>
#include <unordered_set>

using namespace std;

const int SIZE = 9;

int score[SIZE][SIZE] = {
    {10, 10, 10, 9, 9, 9, 9, 9, 9},
    {10, 10, 10, 9, 9, 9, 9, 9, 9},
    {10, 10, 10, 9, 9, 9, 9, 9, 9},
    {8, 8, 8, 7, 7, 7, 7, 7, 7},
    {8, 8, 8, 7, 7, 7, 7, 7, 7},
    {8, 8, 8, 7, 7, 7, 7, 7, 7},
    {6, 6, 6, 6, 6, 6, 6, 6, 6},
    {6, 6, 6, 6, 6, 6, 6, 6, 6},
    {6, 6, 6, 6, 6, 6, 6, 6, 6}
};

vector<vector<int>> board(SIZE, vector<int>(SIZE, 0));
int totalScore = 0;
bool solved = false;

bool isValid(int row, int col, int num) {
    for (int i = 0; i < SIZE; i++) {
        if (board[row][i] == num || board[i][col] == num) return false;
    }
    int boxRow = row / 3 * 3;
    int boxCol = col / 3 * 3;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (board[boxRow + i][boxCol + j] == num) return false;
        }
    }
    return true;
}

void backtrack(int index) {
    if (index == SIZE * SIZE) {
        solved = true;
        return;
    }
    int row = index / SIZE;
    int col = index % SIZE;
    if (board[row][col] != 0) {
        backtrack(index + 1);
        if (solved) return;
    } else {
        for (int num = 1; num <= 9; num++) {
            if (isValid(row, col, num)) {
                board[row][col] = num;
                totalScore += score[row][col] * num;
                backtrack(index + 1);
                if (solved) return;
                totalScore -= score[row][col] * num;
                board[row][col] = 0;
            }
        }
    }
}

int main() {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            cin >> board[i][j];
        }
    }

    backtrack(0);

    if (solved) {
        cout << totalScore << endl;
    } else {
        cout << -1 << endl;
    }

    return 0;