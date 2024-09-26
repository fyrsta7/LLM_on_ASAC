#include <iostream>

long long gcd(long long a, long long b) {
    while (b != 0) {
        long long t = b;
        b = a % b;
        a = t;
    }
    return a;
}

long long extended_gcd(long long a, long long b, long long &x, long long &y) {
    if (b == 0) {
        x = 1;
        y = 0;
        return a;
    }
    long long x1, y1;
    long long d = extended_gcd(b, a % b, x1, y1);
    x = y1;
    y = x1 - y1 * (a / b);
    return d;
}

int main() {
    long long a, b;
    std::cin >> a >> b;

    if (gcd(a, b) != 1) {
        return -1; // No solution if a and b are not coprime
    }

    long long x, y;
    extended_gcd(a, b, x, y);

    x = (x % b + b) % b; // Ensure x is positive
    std::cout << x << std::endl;

    return 0;
}
