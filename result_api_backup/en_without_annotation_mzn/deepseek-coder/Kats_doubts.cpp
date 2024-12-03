#include <iostream>
#include <algorithm>

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
    std::cin >> a >> b;
    
    int max_ans = 2000;
    int gcd_ab = gcd(a, b);
    
    if (gcd_ab == 1) {
        std::cout << max_ans << std::endl;
    } else {
        int max_multiple = (max_ans / a) * a + (max_ans / b) * b;
        int ans = max_ans;
        while (ans == (ans / a) * a + (ans / b) * b) {
            ans--;
        }
        std::cout << ans << std::endl;
    }
    
    return 0;
}
