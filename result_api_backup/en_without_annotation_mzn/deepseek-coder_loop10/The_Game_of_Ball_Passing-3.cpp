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
    int bound = 1 << m;
    vector<vector<int>> paths;

    for (int i = 0; i < bound; ++i) {
        vector<int> path(m + 1);
        path[0] = 1;
        path[m] = 1;
        bool valid = true;
        for (int j = 1; j < m; ++j) {
            path[j] = (i >> (m - j - 1)) & 1 ? n : 1;
            if (!neighbor(path[j - 1], path[j])) {
                valid = false;
                break;
            }
        }
        if (valid && neighbor(path[m - 1], path[m])) {
            if (isUnique(paths, path)) {
                paths.push_back(path);
            }
        }
    }

    cout << paths.size() << endl;
    return 0;
}