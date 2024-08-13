#include <iostream>

long long extendedGCD(long long a, long long b, long long &x, long long &y) {
    if (a == 0) {
        x = 0;
        y = 1;
        return b;
    }
    long long x1, y1;
    long long gcd = extendedGCD(b % a, a, x1, y1);
    x = y1 - (b / a) * x1;
    y = x1;
    return gcd;
}

long long modInverse(long long a, long long b) {
    long long x, y;
    long long g = extendedGCD(a, b, x, y);
    if (g != 1) {
        return -1; // Inverse doesn't exist
    } else {
        // x might be negative, so we need to make it positive
        long long res = (x % b + b) % b;
        return res;
    }
}

int main() {
    long long a, b;
    std::cin >> a >> b;
    std::cout << modInverse(a, b) << std::endl;
    return 0;
}