#include <iostream>

int gcd(int a, int b) {
    while (b != 0) {
        int t = b;
        b = a % b;
        a = t;
    }
    return a;
}

int main() {
    int a, b;
    std::cin >> a >> b;
    if (gcd(a, b) == 1) {
        std::cout << (a - 1) * (b - 1) - 1 << std::endl;
    }
    return 0;
}