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
    
    vector<string> result = minefield;
    
    int dx[] = {-1, -1, -1, 0, 0, 1, 1, 1};
    int dy[] = {-1, 0, 1, -1, 1, -1, 0, 1};
    
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            if (minefield[i][j] == '?') {
                int mineCount = 0;
                for (int k = 0; k < 8; ++k) {
                    int ni = i + dx[k];
                    int nj = j + dy[k];
                    if (ni >= 0 && ni < n && nj >= 0 && nj < m && minefield[ni][nj] == '*') {
                        mineCount++;
                    }
                }
                result[i][j] = mineCount + '0';
            }
        }
    }
    
    for (const auto& row : result) {
        cout << row << '\n';
    }
    
    return 0;
}