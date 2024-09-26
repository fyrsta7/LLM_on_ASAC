#include <bits/stdc++.h>
using namespace std;

int n, m, bound;
int num;
vector<vector<int>> balls;
vector<vector<int>> results;

// Predicate to check if two values are neighbors
bool neighbor(int a, int b) {
    return abs(a - b) == 1 || (a == n && b == 1) || (a == 1 && b == n);
}

// Checking if the configuration satisfies the constraints
bool isValid(int idx) {
    for (int i = 1; i < idx; ++i) {
        if (balls[i][0] != 1 || balls[i][m] != 1)
            return false;
        for (int j = 0; j < m; ++j) {
            if (!neighbor(balls[i][j], balls[i][j+1]))
                return false;
        }
    }
    for (int j = 1; j < idx; ++j) {
        for (int k = j + 1; k <= idx; ++k) {
            bool allDifferent = false;
            for (int l = 0; l <= m; ++l) {
                if (balls[j][l] != balls[k][l]) {
                    allDifferent = true;
                    break;
                }
            }
            if (!allDifferent)
                return false;
        }
    }
    return true;
}

void solve() {
    for (num = bound; num >= 0; --num) {
        bool valid = true;
        balls.resize(num, vector<int>(m+1, 0));
        for (int i = 1; i <= num; ++i) {
            for (int j = 0; j <= m; ++j) {
                balls[i-1][j] = (i + j) % n + 1; // Sample generation
            }
        }
        if (isValid(num - 1)) {
            results = balls;
            break;
        }
    }
    cout << num << endl;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n >> m;
    bound = pow(2, m);
    solve();
    return 0;
}