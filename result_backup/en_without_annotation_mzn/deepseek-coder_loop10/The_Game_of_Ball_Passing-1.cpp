#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int n, m;

bool neighbor(int a, int b) {
    return abs(a - b) == 1 || (a == n && b == 1) || (a == 1 && b == n);
}

bool valid_path(const vector<int>& path) {
    if (path.front() != 1 || path.back() != 1) return false;
    for (int i = 0; i < m; ++i) {
        if (!neighbor(path[i], path[i + 1])) return false;
    }
    return true;
}

int main() {
    cin >> n >> m;
    int bound = 1 << m;
    vector<vector<int>> paths;

    for (int i = 0; i < bound; ++i) {
        vector<int> path(m + 1);
        for (int j = 0; j <= m; ++j) {
            path[j] = (i >> j) & 1 ? n : 1;
        }
        if (valid_path(path)) {
            paths.push_back(path);
        }
    }

    int num = 0;
    vector<bool> used(bound, false);

    for (int i = 0; i < paths.size(); ++i) {
        if (used[i]) continue;
        ++num;
        for (int j = i + 1; j < paths.size(); ++j) {
            bool conflict = false;
            for (int k = 0; k <= m; ++k) {
                if (paths[i][k] == paths[j][k]) {
                    conflict = true;
                    break;
                }
            }
            if (!conflict) used[j] = true;
        }
    }

    cout << num << endl;
    return 0;
}