#include <iostream>
#include <algorithm>

using namespace std;

int gcd(int a, int b) {
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

int main() {
    int a, b;
    cin >> a >> b;

    int g = gcd(a, b);
    int max_ans = 2000;

    for (int ans = max_ans; ans >= 1; --ans) {
        bool valid = true;
        for (int i = 2; i <= min(a, b); ++i) {
            if (a % i == 0 && b % i == 0) {
                valid = false;
                break;
            }
        }
        if (valid) {
            cout << ans << endl;
            return 0;
        }
    }

    cout << 1 << endl;
    return 0;
}