#include <iostream>
#include <vector>

using namespace std;

int main() {
    int n, m;
    cin >> n >> m;

    vector<string> minefield(n);
    for (int i = 0; i < n; ++i) {
        cin >> minefield[i];
    }

    vector<string> result(n, string(m, '0'));

    // Directions for 8 neighboring cells
    int directions[8][2] = { {-1, -1}, {-1, 0}, {-1, 1}, 
                             {0, -1},          {0, 1}, 
                             {1, -1}, {1, 0}, {1, 1} };

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            if (minefield[i][j] == '*') {
                result[i][j] = '*';
                // Increment counts in surrounding cells
                for (auto& dir : directions) {
                    int ni = i + dir[0], nj = j + dir[1];
                    if (ni >= 0 && ni < n && nj >= 0 && nj < m 
                        && result[ni][nj] != '*') {
                        result[ni][nj]++;
                    }
                }
            }
        }
    }

    for (const string& row : result) {
        cout << row << endl;
    }

    return 0;
}