#include <iostream>
#include <vector>
#include <algorithm>

int main() {
    std::vector<int> budget(12);
    for (int i = 0; i < 12; ++i) {
        std::cin >> budget[i];
    }

    std::vector<int> left(13, 0);
    int total = 0;
    int min_left = 0;

    for (int i = 1; i <= 12; ++i) {
        left[i] = (300 + left[i-1] - budget[i-1]) % 100;
        total += ((300 + left[i-1] - budget[i-1]) / 100) * 100;
        min_left = std::min(min_left, left[i]);
    }

    total = static_cast<int>(total * 1.2);

    if (min_left < 0) {
        for (int i = 0; i <= 12; ++i) {
            if (left[i] < 0) {
                std::cout << -i << std::endl;
                return 0;
            }
        }
    } else {
        std::cout << left[12] + total << std::endl;
    }

    return 0;
}