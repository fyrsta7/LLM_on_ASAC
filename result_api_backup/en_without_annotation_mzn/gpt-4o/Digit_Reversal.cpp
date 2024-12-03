#include <iostream>
#include <vector>
#include <cmath>

int main() {
    int n;
    std::cin >> n;
    std::vector<int> digits(10, 0);
    int abs_n = std::abs(n);
    int temp = abs_n;

    for (int i = 0; i < 10; ++i) {
        if (temp == 0) break;
        digits[i] = temp % 10;
        temp /= 10;
    }

    bool leading_zero = true;

    if (n < 0) {
        std::cout << "-";
    } else if (n == 0) {
        std::cout << "0";
    }

    for (int i = 9; i >= 0; --i) {
        if (digits[i] != 0 || !leading_zero) {
            std::cout << digits[i];
            leading_zero = false;
        }
    }

    std::cout << std::endl;

    return 0;
}