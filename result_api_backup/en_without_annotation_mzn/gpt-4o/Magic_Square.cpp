#include <iostream>
#include <vector>
using namespace std;

bool isSafe(vector<vector<int>>& square, int x, int y) {
    return x >= 0 && x < square.size() && y >= 0 && y < square[0].size() && square[x][y] == 0;
}

void printSquare(const vector<vector<int>>& square) {
    for (const auto& row : square) {
        for (int value : row) {
            cout << value << " ";
        }
        cout << endl;
    }
}

bool solveMagicSquare(vector<vector<int>>& square, int x, int y, int num) {
    if (num > square.size() * square.size()) return true;

    if (x < 0) x = square.size() - 1;
    if (y == square.size()) y = 0;

    if (square[x][y] == 0) {
        square[x][y] = num;
        if (solveMagicSquare(square, x - 1, y + 1, num + 1)) return true;
        square[x][y] = 0;
    }

    return isSafe(square, x + 1, y) && solveMagicSquare(square, x + 1, y, num);
}

int main() {
    int N;
    cin >> N;

    vector<vector<int>> square(N, vector<int>(N, 0));

    int startX = 1;
    int startY = N / 2;

    square[startX][startY] = 1;

    solveMagicSquare(square, startX - 1, startY + 1, 2);

    printSquare(square);

    return 0;
}