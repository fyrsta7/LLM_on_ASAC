#include <iostream>
#include <vector>
using namespace std;

void generateMagicSquare(int N) {
    vector<vector<int>> square(N, vector<int>(N, 0));
    int x = 0, y = N / 2;
    for (int num = 1; num <= N * N; ++num) {
        square[x][y] = num;
        int newX = (x - 1 + N) % N;
        int newY = (y + 1) % N;
        if (square[newX][newY] != 0) {
            newX = (x + 1) % N;
            newY = y;
        }
        x = newX;
        y = newY;
    }
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            cout << square[i][j] << (j == N - 1 ? "\n" : " ");
        }
    }
}

int main() {
    int N;
    cin >> N;
    generateMagicSquare(N);
    return 0;
}