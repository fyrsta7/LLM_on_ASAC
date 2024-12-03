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
        bool unique = false;
        for (int l = 0; l <= m; ++l) {
            if (p[l] != path[l]) {
                unique = true;
                break;
            }
        }
        if (!unique) return false;
    }
    return true;
}

void backtrack(vector<vector<int>>& paths, vector<int>& currentPath, int pos) {
    if (pos == m + 1) {
        if (isValidPath(currentPath) && isUnique(paths, currentPath)) {
            paths.push_back(currentPath);
        }
        return;
    }

    for (int i = 1; i <= n; ++i) {
        currentPath[pos] = i;
        backtrack(paths, currentPath, pos + 1);
    }
}

int main() {
    cin >> n >> m;

    vector<vector<int>> paths;
    vector<int> currentPath(m + 1, 1);

    backtrack(paths, currentPath, 1);

    cout << paths.size() << endl;

    return 0;
}