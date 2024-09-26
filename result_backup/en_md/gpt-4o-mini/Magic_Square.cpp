#include <iostream>
#include <vector>
using namespace std;

int main() {
    int N;
    cin >> N;
    vector<vector<int>> magicSquare(N, vector<int>(N, 0));
    
    int num = 1;
    int i = 0, j = N / 2; // Start from the middle of the first row

    while (num <= N * N) {
        magicSquare[i][j] = num;
        num++;
        
        int new_i = (i - 1 + N) % N; // Move up
        int new_j = (j + 1) % N; // Move right
        
        if (magicSquare[new_i][new_j] != 0) { // If the cell is already filled
            i = (i + 1) % N; // Move down
        } else {
            i = new_i;
            j = new_j;
        }
    }
    
    for (const auto& row : magicSquare) {
        for (int k = 0; k < N; k++) {
            cout << row[k] << (k < N - 1 ? " " : "");
        }
        cout << endl;
    }

    return 0;
}