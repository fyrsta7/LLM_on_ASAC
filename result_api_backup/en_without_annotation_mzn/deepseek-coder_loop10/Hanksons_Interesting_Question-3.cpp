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

bool is_valid(int a, int b, int g, int l) {
    return gcd(a, b) == g && lcm(a, b) == l;
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
        int a = numbers[i][0], g = numbers[i][1], b = numbers[i][2], l = numbers[i][3];
        for (int x = 1; x <= 100; ++x) {
            if (is_valid(a, x, g, l) && is_valid(b, x, g, l)) {
                ans[i][p[i]++] = x;
            }
        }
    }

    int total_p = accumulate(p.begin(), p.end(), 0);
    cout << total_p << endl;

    return 0;
}