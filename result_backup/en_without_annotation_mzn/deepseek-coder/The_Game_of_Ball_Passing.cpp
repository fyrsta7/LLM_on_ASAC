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

int main() {
    cin >> n >> m;
    int bound = 1 << m;
    vector<vector<int>> validPaths;

    for (int i = 0; i < bound; ++i) {
        vector<int> path(m + 1);
        for (int j = 0; j < m; ++j) {
            path[j + 1] = (i >> j) & 1 ? 1 : n;
        }
        if (isValidPath(path)) {
            validPaths.push_back(path);
        }
    }

    int maxNum = 0;
    for (int i = 0; i < validPaths.size(); ++i) {
        for (int j = i + 1; j < validPaths.size(); ++j) {
            bool unique = false;
            for (int l = 1; l <= m + 1; ++l) {
                if (validPaths[i][l] != validPaths[j][l]) {
                    unique = true;
                    break;
                }
            }
            if (unique) {
                maxNum = max(maxNum, 2);
            }
        }
    }

    cout << maxNum << endl;
    return 0;
}