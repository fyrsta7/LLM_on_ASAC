#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int n, m;

bool neighbor(int a, int b) {
    return abs(a - b) == 1 || (a == n && b == 1) || (a == 1 && b == n);
}

bool isValidPath(const vector<int>& path) {
    for (int j = 0; j < m; ++j) {
        if (!neighbor(path[j], path[j + 1])) {
            return false;
        }
    }
    return true;
}

bool isUnique(const vector<vector<int>>& paths, const vector<int>& path) {
    for (const auto& p : paths) {
        bool same = true;
        for (int l = 0; l <= m; ++l) {
            if (p[l] != path[l]) {
                same = false;
                break;
            }
        }
        if (same) return false;
    }
    return true;
}

int main() {
    cin >> n >> m;

    vector<vector<int>> paths;
    int maxNum = 0;

    for (int i = 0; i < (1 << n); ++i) {
        vector<int> path(m + 1);
        for (int j = 0; j < m; ++j) {
            path[j] = (i >> j) & 1 ? 1 : n;
        }
        path[m] = 1;

        if (isValidPath(path) && isUnique(paths, path)) {
            paths.push_back(path);
            maxNum = max(maxNum, (int)paths.size());
        }
    }

    cout << maxNum << endl;

    return 0;
}