#include <iostream>
#include <vector>
#include <numeric>
#include <algorithm>

using namespace std;

bool gcd(int a, int b, int x) {
    return a % x == 0 && b % x == 0 && std::gcd(a, b) == x;
}

bool lcm(int a, int b, int x) {
    return (a * b) % x == 0 && std::gcd(a, b) == (a * b / x);
}

int main() {
    int n;
    cin >> n;
    vector<vector<int>> numbers(n, vector<int>(4));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < 4; ++j) {
            cin >> numbers[i][j];
        }
    }

    int maxL = 100;
    vector<vector<int>> ans(n, vector<int>(maxL));
    vector<int> p(n, 0);

    for (int i = 0; i < n; ++i) {
        for (int j = 1; j <= maxL; ++j) {
            bool valid = true;
            for (int k = 0; k < p[i]; ++k) {
                if (ans[i][k] == j) {
                    valid = false;
                    break;
                }
            }
            if (!valid) continue;

            bool satisfiesConstraints = true;
            for (int ti = 0; ti <= p[i]; ++ti) {
                if (!gcd(numbers[i][0], j, numbers[i][1]) || !lcm(numbers[i][2], j, numbers[i][3])) {
                    satisfiesConstraints = false;
                    break;
                }
            }

            if (satisfiesConstraints) {
                ans[i][p[i]] = j;
                ++p[i];
            }
        }
    }

    for (int i = 0; i < n; ++i) {
        if (i > 0) cout << " ";
        cout << p[i];
    }
    cout << endl;

    return 0;
}