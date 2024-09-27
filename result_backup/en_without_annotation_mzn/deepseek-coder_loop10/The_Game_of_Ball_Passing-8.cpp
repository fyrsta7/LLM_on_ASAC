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

bool arePathsDistinct(const vector<vector<int>>& paths, const vector<int>& newPath) {
    for (const auto& path : paths) {
        bool distinct = false;
        for (int l = 0; l <= m; ++l) {
            if (path[l] != newPath[l]) {
                distinct = true;
                break;
            }
        }
        if (!distinct) return false;
    }
    return true;
}

int main() {
    cin >> n >> m;
    int bound = pow(2, m);
    vector<vector<int>> paths;
    int maxNum = 0;

    for (int num = 0; num < bound; ++num) {
        vector<int> path(m + 1, 1);
        bool valid = true;
        for (int i = 0; i < num; ++i) {
            if (!isValidPath(path) || !arePathsDistinct(paths, path)) {
                valid = false;
                break;
            }
            paths.push_back(path);
        }
        if (valid) {
            maxNum = max(maxNum, num);
        }
    }

    cout << maxNum << endl;
    return 0;
}