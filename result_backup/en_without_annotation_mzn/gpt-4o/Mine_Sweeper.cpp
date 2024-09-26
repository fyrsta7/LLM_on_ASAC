#include <iostream>
#include <vector>
using namespace std;

vector<vector<int>> calculate_b(const vector<vector<int>>& a, int n, int m) {
    vector<vector<int>> b(n, vector<int>(m, 0));
    vector<int> dx = {-1, -1, -1, 0, 0, 1, 1, 1};
    vector<int> dy = {-1, 0, 1, -1, 1, -1, 0, 1};

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            if (a[i][j] == 1) {
                b[i][j] = -1;
            } else {
                int sum = 0;
                for (int k = 0; k < 8; ++k) {
                    int ni = i + dx[k];
                    int nj = j + dy[k];
                    if (ni >= 0 && ni < n && nj >= 0 && nj < m && a[ni][nj] == 1) {
                        sum += 1;
                    }
                }
                b[i][j] = sum;
            }
        }
    }
    return b;
}

int main() {
    int n, m;
    cin >> n >> m;
    vector<vector<int>> a(n, vector<int>(m));
    
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            cin >> a[i][j];
        }
    }

    vector<vector<int>> b = calculate_b(a, n, m);

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            if (b[i][j] == -1) {
                cout << "*";
            } else {
                cout << b[i][j];
            }
            if (j == m - 1) {
                cout << "\n";
            }
        }
    }

    return 0;
}