#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

int n, m;

bool neighbor(int a, int b) {
    return abs(a - b) == 1 || (a == n && b == 1) || (a == 1 && b == n);
}

int main() {
    cin >> n >> m;
    int bound = 1 << m;
    vector<vector<int>> balls(bound, vector<int>(m + 1));
    int num = 0;

    for (int i = 0; i < bound; ++i) {
        bool valid = true;
        for (int j = 0; j < m; ++j) {
            balls[i][j + 1] = (i >> j) & 1 ? 1 : n;
            if (j > 0 && !neighbor(balls[i][j], balls[i][j + 1])) {
                valid = false;
                break;
            }
        }
        if (valid && balls[i][1] == 1 && balls[i][m] == 1) {
            bool unique = true;
            for (int j = 0; j < num; ++j) {
                bool same = true;
                for (int k = 1; k <= m; ++k) {
                    if (balls[i][k] != balls[j][k]) {
                        same = false;
                        break;
                    }
                }
                if (same) {
                    unique = false;
                    break;
                }
            }
            if (unique) {
                balls[num++] = balls[i];
            }
        }
    }

    cout << num << endl;
    return 0;
}