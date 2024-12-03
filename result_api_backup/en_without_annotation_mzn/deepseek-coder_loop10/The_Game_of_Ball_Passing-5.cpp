#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

int n, m;

bool neighbor(int a, int b) {
    return abs(a - b) == 1 || (a == n && b == 1) || (a == 1 && b == n);
}

bool isValid(vector<int>& path) {
    if (path.front() != 1 || path.back() != 1) return false;
    for (int i = 0; i < m; ++i) {
        if (!neighbor(path[i], path[i + 1])) return false;
    }
    return true;
}

bool isUnique(vector<vector<int>>& paths, vector<int>& path) {
    for (auto& p : paths) {
        bool same = true;
        for (int i = 0; i <= m; ++i) {
            if (p[i] != path[i]) {
                same = false;
                break;
            }
        }
        if (same) return false;
    }
    return true;
}

void findPaths(vector<vector<int>>& paths, vector<int>& path, int pos) {
    if (pos > m) {
        if (isValid(path) && isUnique(paths, path)) {
            paths.push_back(path);
        }
        return;
    }
    for (int i = 1; i <= n; ++i) {
        path[pos] = i;
        findPaths(paths, path, pos + 1);
    }
}

int main() {
    cin >> n >> m;
    vector<vector<int>> paths;
    vector<int> path(m + 1);
    findPaths(paths, path, 0);
    cout << paths.size() << endl;
    return 0;
}