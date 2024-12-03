#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>

using namespace std;

int gcd(int a, int b) {
    while (b) {
        a %= b;
        swap(a, b);
    }
    return a;
}

int lcm(int a, int b) {
    return a / gcd(a, b) * b;
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

    vector<int> p(n, 0);
    vector<vector<int>> ans(n, vector<int>(100, 0));

    for (int i = 0; i < n; ++i) {
        int a = numbers[i][0], b = numbers[i][1], c = numbers[i][2], d = numbers[i][3];
        for (int x = 1; x <= 100; ++x) {
            if (a % x == 0 && b % x == 0 && c * d % x == 0 && gcd(c, d) == c * d / x) {
                ans[i][p[i]++] = x;
            }
        }
    }

    for (int i = 0; i < n; ++i) {
        sort(ans[i].begin(), ans[i].begin() + p[i]);
        p[i] = unique(ans[i].begin(), ans[i].begin() + p[i]) - ans[i].begin();
    }

    int total_p = accumulate(p.begin(), p.end(), 0);
    cout << total_p << endl;

    return 0;
}
