#include <iostream>
#include <cmath>

int gcdExtended(int a, int b, int &x, int &y) {
    if (a == 0) {
        x = 0;
        y = 1;
        return b;
    }
    int x1, y1;
    int gcd = gcdExtended(b % a, a, x1, y1);
    x = y1 - (b / a) * x1;
    y = x1;
    return gcd;
}

int modInverse(int a, int m) {
    int x, y;
    int g = gcdExtended(a, m, x, y);
    if (g != 1) {
        return -1; // Inverse doesn't exist
    } else {
        return (x % m + m) % m;
    }
}

int main() {
    int a, b;
    std::cin >> a >> b;
    int x = modInverse(a, b);
    if (x != -1) {
        std::cout << x << std::endl;
    } else {
        std::cout << "No solution" << std::endl;
    }
    return 0;
}