#include <iostream>
#include <vector>
#include <algorithm>

int main() {
    std::vector<int> budget(12);
    for (int i = 0; i < 12; ++i) {
        std::cin >> budget[i];
    }

    int left = 0;
    int total = 0;
    int deficit_month = -1;

    for (int i = 0; i < 12; ++i) {
        left = (300 + left - budget[i]) % 100;
        if (left < 0 && deficit_month == -1) {
            deficit_month = i + 1;
        }
        total += ((300 + left - budget[i]) / 100) * 100;
    }

    if (deficit_month != -1) {
        std::cout << "-" << deficit_month << std::endl;
    } else {
        std::cout << left + total * 1.2 << std::endl;
    }

    return 0;
}