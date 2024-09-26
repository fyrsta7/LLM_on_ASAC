#include <iostream>
#include <vector>
#include <cmath>

int main() {
    int n;
    std::cin >> n;
    std::vector<int> coefficient(n + 2);
    for (int i = 1; i <= n + 1; ++i) {
        std::cin >> coefficient[i];
    }

    for (int i = 1; i <= n; ++i) {
        if (coefficient[i] != 0) {
            if (coefficient[i] < 0) {
                std::cout << "-";
            } else if (i > 1) {
                std::cout << "+";
            }

            if (std::abs(coefficient[i]) != 1) {
                std::cout << std::abs(coefficient[i]);
            }

            std::cout << "x";
            if (n - i + 1 != 1) {
                std::cout << "^" << (n - i + 1);
            }
        }
    }

    if (coefficient[n + 1] != 0) {
        if (coefficient[n + 1] > 0) {
            std::cout << "+";
        } else {
            std::cout << "-";
        }
        std::cout << std::abs(coefficient[n + 1]);
    }

    return 0;
}
