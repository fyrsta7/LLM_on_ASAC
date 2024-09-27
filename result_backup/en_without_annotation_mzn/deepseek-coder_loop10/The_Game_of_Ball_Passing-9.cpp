#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

int n, m;
int bound;
vector<vector<int>> balls;

bool neighbor(int a, int b) {
    return abs(a - b) == 1 || (a == n && b == 1) || (a == 1 && b == n);
}

bool isValid(int num) {
    for (int i = 0; i < num; ++i) {
        if (balls[i][0] != 1 || balls[i][m] != 1) return false;
        for (int j = 0; j < m - 1; ++j) {
            if (!neighbor(balls[i][j], balls[i][j + 1])) return false;
        }
    }
    for (int j = 0; j < num; ++j) {
        for (int k = j + 1; k < num; ++k) {
            bool unique = false;
            for (int l = 0; l <= m; ++l) {
                if (balls[j][l] != balls[k][l]) {
                    unique = true;
                    break;
                }
            }
            if (!unique) return false;
        }
    }
    return true;
}

int main() {
    cin >> n >> m;
    bound = pow(2, m);
    balls.resize(bound, vector<int>(m + 1));

    int maxNum = 0;
    for (int num = 0; num < bound; ++num) {
        for (int i = 0; i < num; ++i) {
            for (int j = 0; j <= m; ++j) {
                balls[i][j] = (i >> j) & 1 ? 1 : n;
            }
        }
        if (isValid(num)) {
            maxNum = num;
        }
    }

    cout << maxNum << endl;
    return 0;
}