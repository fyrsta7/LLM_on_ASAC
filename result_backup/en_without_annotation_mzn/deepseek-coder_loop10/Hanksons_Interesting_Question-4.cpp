#include <iostream>
#include <vector>
#include <algorithm>

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
    return a * (b / gcd(a, b));
}

bool isValid(int a, int b, int g, int l) {
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
        int count = 0;
        for (int x = 1; x <= 100; ++x) {
            if (isValid(numbers[i][0], x, numbers[i][1], numbers[i][2])) {
                bool unique = true;
                for (int j = 0; j < count; ++j) {
                    if (ans[i][j] == x) {
                        unique = false;
                        break;
                    }
                }
                if (unique) {
                    ans[i][count++] = x;
                }
            }
        }
        p[i] = count;
    }

    int total = 0;
    for (int i = 0; i < n; ++i) {
        total += p[i];
    }

    cout << total << endl;

    return 0;
}
