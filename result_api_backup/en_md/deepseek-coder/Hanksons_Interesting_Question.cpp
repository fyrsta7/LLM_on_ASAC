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
    return a / gcd(a, b) * b;
}

int solve(int a0, int a1, int b0, int b1) {
    int count = 0;
    for (int x = 1; x * x <= b1; ++x) {
        if (b1 % x == 0) {
            if (gcd(x, a0) == a1 && lcm(x, b0) == b1) {
                count++;
            }
            int y = b1 / x;
            if (x != y && gcd(y, a0) == a1 && lcm(y, b0) == b1) {
                count++;
            }
        }
    }
    return count;
}

int main() {
    int n;
    cin >> n;
    while (n--) {
        int a0, a1, b0, b1;
        cin >> a0 >> a1 >> b0 >> b1;
        cout << solve(a0, a1, b0, b1) << endl;
    }
    return 0;
}
