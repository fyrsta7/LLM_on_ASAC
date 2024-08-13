#include <iostream>
#include <vector>

using namespace std;

vector<vector<int>> generateMagicSquare(int n) {
    vector<vector<int>> magicSquare(n, vector<int>(n, 0));
    int number = 1;
    int row = 0, col = n / 2;

    while (number <= n * n) {
        magicSquare[row][col] = number;
        number++;
        int newRow = (row - 1 + n) % n;
        int newCol = (col + 1) % n;

        if (magicSquare[newRow][newCol] != 0) {
            newRow = (row + 1) % n;
            newCol = col;
        }

        row = newRow;
        col = newCol;
    }

    return magicSquare;
}

int main() {
    int n;
    cin >> n;

    vector<vector<int>> magicSquare = generateMagicSquare(n);

    for (const auto &row : magicSquare) {
        for (int num : row) {
            cout << num << " ";
        }
        cout << endl;
    }

    return 0;
}