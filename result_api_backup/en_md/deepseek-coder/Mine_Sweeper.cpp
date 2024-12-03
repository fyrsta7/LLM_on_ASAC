#include <iostream>
#include <vector>
using namespace std;

int main() {
    int n, m;
    cin >> n >> m;
    vector<vector<char>> field(n, vector<char>(m));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            cin >> field[i][j];
        }
    }

    vector<vector<int>> mines(n, vector<int>(m, 0));
    vector<pair<int, int>> directions = {{-1, -1}, {-1, 0}, {-1, 1}, {0, -1}, {0, 1}, {1, -1}, {1, 0}, {1, 1}};

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            if (field[i][j] == '*') {
                for (auto &dir : directions) {
                    int ni = i + dir.first, nj = j + dir.second;
                    if (ni >= 0 && ni < n && nj >= 0 && nj < m) {
                        mines[ni][nj]++;
                    }
                }
            }
        }
    }

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            if (field[i][j] == '*') {
                cout << '*';
            } else {
                cout << mines[i][j];
            }
        }
        cout << endl;
    }

    return 0;
}