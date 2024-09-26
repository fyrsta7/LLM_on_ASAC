#include <iostream>
#include <cmath>

int main() {
    int n, m, k, x;
    std::cin >> n >> m >> k >> x;

    int rounds = std::pow(10, k);
    int period = n;

    if (m % n == 0) {
        std::cout << x << std::endl;
        return 0;
    }

    int current = x;
    for (int i = 1; i <= rounds; ++i) {
        current = (current + m) % n;
    }

    std::cout << current << std::endl;
    return 0;
}