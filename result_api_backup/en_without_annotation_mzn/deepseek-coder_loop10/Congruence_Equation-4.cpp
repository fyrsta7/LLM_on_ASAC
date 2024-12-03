#include <iostream>
#include <numeric>

int main() {
    int a, b;
    std::cin >> a >> b;

    // Extended Euclidean Algorithm to find x and y such that a*x + b*y = gcd(a, b)
    int x, y;
    int gcd = std::gcd(a, b);
    if (gcd != 1) {
        std::cout << "No solution exists" << std::endl;
        return 0;
    }

    // Using the extended Euclidean algorithm to find the modular inverse
    int original_b = b;
    x = 1, y = 0;
    int x1 = 0, y1 = 1, a1 = a, b1 = b;
    while (b1 != 0) {
        int q = a1 / b1;
        std::tie(x, x1) = std::make_tuple(x1, x - q * x1);
        std::tie(y, y1) = std::make_tuple(y1, y - q * y1);
        std::tie(a1, b1) = std::make_tuple(b1, a1 - q * b1);
    }

    // Ensure x is positive
    if (x < 0) {
        x += original_b;
    }

    std::cout << x << std::endl;
    return 0;
}