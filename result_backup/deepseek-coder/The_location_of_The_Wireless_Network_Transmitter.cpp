#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    int d, n;
    cin >> d >> n;
    vector<vector<int>> grid(129, vector<int>(129, 0));
    vector<vector<int>> prefixSum(130, vector<int>(130, 0));

    for (int i = 0; i < n; ++i) {
        int x, y, k;
        cin >> x >> y >> k;
        grid[x][y] = k;
    }

    for (int i = 0; i <= 128; ++i) {
        for (int j = 0; j <= 128; ++j) {
            prefixSum[i + 1][j + 1] = grid[i][j] + prefixSum[i][j + 1] + prefixSum[i + 1][j] - prefixSum[i][j];
        }
    }

    int maxPublicSpaces = 0, maxSchemes = 0;

    for (int i = 0; i <= 128; ++i) {
        for (int j = 0; j <= 128; ++j) {
            int x1 = max(0, i - d);
            int y1 = max(0, j - d);
            int x2 = min(128, i + d);
            int y2 = min(128, j + d);
            int publicSpaces = prefixSum[x2 + 1][y2 + 1] - prefixSum[x1][y2 + 1] - prefixSum[x2 + 1][y1] + prefixSum[x1][y1];
            if (publicSpaces > maxPublicSpaces) {
                maxPublicSpaces = publicSpaces;
                maxSchemes = 1;
            } else if (publicSpaces == maxPublicSpaces) {
                ++maxSchemes;
            }
        }
    }

    cout << maxSchemes << " " << maxPublicSpaces << endl;
    return 0;
}
