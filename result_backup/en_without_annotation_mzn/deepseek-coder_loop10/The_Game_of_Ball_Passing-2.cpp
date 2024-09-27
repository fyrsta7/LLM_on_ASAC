#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

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
    int bound = pow(2, m);
    vector<vector<int>> paths;
    int maxNum = 0;

    for (int num = 0; num < bound; ++num) {
        vector<vector<int>> currentPaths;
        bool valid = true;

        for (int i = 0; i < num; ++i) {
            vector<int> path(m + 1);
            for (int j = 0; j <= m; ++j) {
                path[j] = (i >> j) & 1 ? n : 1;
            }
            if (isValidPath(path) && isUnique(currentPaths, path)) {
                currentPaths.push_back(path);
            } else {
                valid = false;
                break;
            }
        }

        if (valid) {
            maxNum = num;
        }
    }

    cout << maxNum << endl;
    return 0;
}