#include <iostream>
#include <vector>
using namespace std;

int countDigit(int num, int digit) {
    int count = 0;
    while (num > 0) {
        if (num % 10 == digit) count++;
        num /= 10;
    }
    return count;
}

int main() {
    int n, x;
    cin >> n >> x;
    
    int ans = 0;
    for (int i = 1; i <= n; ++i) {
        ans += countDigit(i, x);
    }
    
    cout << ans << endl;
    return 0;
}