#include <iostream>
#include <vector>

using namespace std;

int main() {
    int n, m;
    cin >> n >> m;
    vector<vector<int>> a(n, vector<int>(m));
    vector<vector<int>> b(n, vector<int>(m, 0));

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            cin >> a[i][j];
        }
    }

    auto getval = [&](int x, int y) -> int {
        if (x < 0 || x >= n || y < 0 || y >= m) return 0;
        return a[x][y];
    };

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            if (a[i][j] == 1) {
                b[i][j] = -1;
            } else {
                b[i][j] = getval(i - 1, j - 1) + getval(i - 1, j) + getval(i - 1, j + 1) +
                          getval(i, j - 1) + getval(i, j + 1) +
                          getval(i + 1, j - 1) + getval(i + 1, j) + getval(i + 1, j + 1);
            }
        }
    }

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            if (b[i][j] == -1) {
                cout << "*";
            } else {
                cout << b[i][j];
            }
            if (j < m - 1) cout << " ";
        }
        cout << endl;
    }

    return 0;
}
