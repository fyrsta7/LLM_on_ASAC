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

    int g = gcd(a, b);
    int max_ans = 2000;
    int ans = max_ans - (max_ans / a + max_ans / b) * g;

    std::cout << ans << std::endl;
    return 0;
}