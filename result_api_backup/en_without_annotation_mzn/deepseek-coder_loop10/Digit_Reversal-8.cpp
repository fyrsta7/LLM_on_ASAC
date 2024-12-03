#include <iostream>
#include <vector>
#include <cmath>

int main() {
    int n;
    std::cin >> n;

    if (n == 0) {
        std::cout << "0" << std::endl;
        return 0;
    }

    std::vector<int> digits(10, 0);
    int num = std::abs(n);
    int i = 0;

    while (num > 0) {
        digits[i++] = num % 10;
        num /= 10;
    }

    if (n < 0) {
        std::cout << "-";
    }

    bool leading = true;
    for (int j = 0; j < 10; ++j) {
        if (digits[j] != 0) {
            leading = false;
        }
        if (!leading) {
            std::cout << digits[j];
        }
    }

    std::cout << std::endl;
    return 0;
}