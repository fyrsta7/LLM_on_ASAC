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
    path1.reserve(m + n - 1);
    path2.reserve(m + n - 1);

    for (int i = 0; i < m; ++i) {
        path1.emplace_back(i, 0);
    }
    for (int j = 1; j < n; ++j) {
        path1.emplace_back(m - 1, j);
    }

    for (int j = 0; j < n; ++j) {
        path2.emplace_back(m - 1, j);
    }
    for (int i = m - 2; i >= 0; --i) {
        path2.emplace_back(i, n - 1);
    }

    int maxValue = calculateValue(path1, path2);

    cout << maxValue << endl;

    return 0;
}
