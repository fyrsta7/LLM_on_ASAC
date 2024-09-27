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
    
    if (g > 1) {
        cout << max_ans << endl;
    } else {
        int ans = max_ans;
        while (ans % a == 0 || ans % b == 0) {
            ans--;
        }
        cout << ans << endl;
    }
    
    return 0;
}