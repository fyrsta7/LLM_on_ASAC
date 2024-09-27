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
    int min_left = 0;
    int min_month = 0;

    for (int i = 0; i < 12; ++i) {
        left = (300 + left - budget[i]) % 100;
        int savings = (300 + left - budget[i]) / 100;
        total += savings * 100;
        if (left < min_left) {
            min_left = left;
            min_month = i + 1;
        }
    }

    if (min_left < 0) {
        std::cout << "-" << min_month << std::endl;
    } else {
        total = static_cast<int>(total * 1.2);
        std::cout << left + total << std::endl;
    }

    return 0;
}