#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int m, n;
vector<vector<int>> students;

int calculateValue(const vector<pair<int, int>>& path1, const vector<pair<int, int>>& path2) {
    int value = 0;
    for (const auto& p : path1) {
        value += students[p.first][p.second];
    }
    for (const auto& p : path2) {
        value += students[p.first][p.second];
    }
    return value;
}

int main() {
    cin >> m >> n;
    students.resize(m, vector<int>(n));
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            cin >> students[i][j];
        }
    }

    vector<pair<int, int>> path1, path2;
    path1.emplace_back(0, 0);
    path2.emplace_back(m-1, n-1);

    for (int i = 0; i < m + n - 2; ++i) {
        if (path1.back().first < m - 1) {
            path1.emplace_back(path1.back().first + 1, path1.back().second);
        } else {
            path1.emplace_back(path1.back().first, path1.back().second + 1);
        }

        if (path2.back().second > 0) {
            path2.emplace_back(path2.back().first, path2.back().second - 1);
        } else {
            path2.emplace_back(path2.back().first - 1, path2.back().second);
        }
    }

    int maxValue = calculateValue(path1, path2);
    cout << maxValue << endl;

    return 0;
}
