#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

int main() {
    int n, m, r, c;
    cin >> n >> m >> r >> c;
    vector<vector<int>> a(n, vector<int>(m));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            cin >> a[i][j];
        }
    }

    int minScore = INT_MAX;
    vector<int> rowCombination(n, 0);
    for (int i = 0; i < r; ++i) rowCombination[n - 1 - i] = 1;

    do {
        vector<int> colCombination(m, 0);
        for (int i = 0; i < c; ++i) colCombination[m - 1 - i] = 1;

        do {
            vector<int> selectedRows, selectedCols;
            for (int i = 0; i < n; ++i) if (rowCombination[i]) selectedRows.push_back(i);
            for (int i = 0; i < m; ++i) if (colCombination[i]) selectedCols.push_back(i);

            int score = 0;
            for (int i = 0; i < r; ++i) {
                for (int j = 0; j < c; ++j) {
                    if (i > 0) score += abs(a[selectedRows[i]][selectedCols[j]] - a[selectedRows[i - 1]][selectedCols[j]]);
                    if (j > 0) score += abs(a[selectedRows[i]][selectedCols[j]] - a[selectedRows[i]][selectedCols[j - 1]]);
                }
            }
            minScore = min(minScore, score);
        } while (next_permutation(colCombination.begin(), colCombination.end()));
    } while (next_permutation(rowCombination.begin(), rowCombination.end()));

    cout << minScore << endl;
    return 0;
}
