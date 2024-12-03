#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>

using namespace std;

int gcd(int a, int b) {
    while (b != 0) {
        int t = b;
        b = a % b;
        a = t;
    }
    return a;
}

int lcm(int a, int b) {
    return a / gcd(a, b) * b;
}

bool isValid(int a, int b, int x, int y) {
    return gcd(a, x) == b && lcm(y, x) == a;
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
        int count = 0;
        for (int x = 1; x <= 100; ++x) {
            if (isValid(numbers[i][0], numbers[i][1], x, numbers[i][2])) {
                ans[i][count++] = x;
            }
        }
        p[i] = count;
    }

    int total = accumulate(p.begin(), p.end(), 0);
    cout << total << endl;

    return 0;
}
