#include <iostream>
#include <cmath>

int main() {
    int n, m, k, x;
    std::cin >> n >> m >> k >> x;

    int rounds = std::pow(10, k);
    int cycle_length = std::lcm(n, m);
    int effective_rounds = rounds % cycle_length;

    for (int i = 0; i < effective_rounds; ++i) {
        x = (x + m) % n;
    }

    std::cout << x << std::endl;
    return 0;
}