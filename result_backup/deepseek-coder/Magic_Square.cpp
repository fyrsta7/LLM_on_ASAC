#include <iostream>
#include <vector>

using namespace std;

int main() {
    int N;
    cin >> N;
    vector<vector<int>> magicSquare(N, vector<int>(N, 0));

    int num = 1;
    int i = 0, j = N / 2;

    while (num <= N * N) {
        magicSquare[i][j] = num++;
        int newI = (i - 1 + N) % N;
        int newJ = (j + 1) % N;

        if (magicSquare[newI][newJ] != 0) {
            newI = (i + 1) % N;
            newJ = j;
        }

        i = newI;
        j = newJ;
    }

    for (int row = 0; row < N; ++row) {
        for (int col = 0; col < N; ++col) {
            cout << magicSquare[row][col] << " ";
        }
        cout << endl;
    }

    return 0;
}