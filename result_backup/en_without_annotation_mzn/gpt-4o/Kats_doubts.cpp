#include <iostream>
#include <algorithm>
using namespace std;

bool gcd_check(int a, int b) {
    for (int i = 2; i <= min(a, b); ++i) {
        if (a % i == 0 && b % i == 0) {
            return false;
        }
    }
    return true;
}

bool is_valid(int ans, int a, int b) {
    for (int num_a = 0; num_a * a <= ans; ++num_a) {
        for (int num_b = 0; num_b * b <= ans; ++num_b) {
            if (num_a * a + num_b * b == ans) {
                return false;
            }
        }
    }
    return true;
}

int main() {
    int a, b;
    cin >> a >> b;
    
    if (!gcd_check(a, b)) {
        cout << -1 << endl; // If a and b are not coprime, no solution exists
        return 0;
    }
    
    const int max_ans = 2000;
    for (int ans = max_ans; ans >= 1; --ans) {
        if (is_valid(ans, a, b)) {
            cout << ans << endl;
            return 0;
        }
    }
    return 0;
}