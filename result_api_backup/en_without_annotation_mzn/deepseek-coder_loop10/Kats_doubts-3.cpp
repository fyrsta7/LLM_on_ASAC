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
    
    int max_ans = 2000;
    int ans = max_ans;
    
    int g = gcd(a, b);
    for (int i = 2; i <= min(a, b); ++i) {
        if (a % i == 0 && b % i == 0) {
            ans = -1;
            break;
        }
    }
    
    if (ans != -1) {
        for (int num_a = 0; num_a <= max_ans; ++num_a) {
            for (int num_b = 0; num_b <= max_ans; ++num_b) {
                if (num_a * a + num_b * b == ans) {
                    ans--;
                    num_a = 0;
                    num_b = 0;
                }
            }
        }
    }
    
    cout << ans << endl;
    return 0;
}