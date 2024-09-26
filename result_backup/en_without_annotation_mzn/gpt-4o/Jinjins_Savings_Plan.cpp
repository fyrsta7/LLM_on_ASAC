#include <iostream>
#include <vector>

std::string solve(const std::vector<int>& budget) {
    std::vector<int> left(13, 0);
    int total = 0;
    for (int i = 1; i <= 12; ++i) {
        left[i] = (300 + left[i - 1] - budget[i - 1]) % 100;
        if (left[i] < 0) {
            return "-" + std::to_string(i);
        }
        total += ((300 + left[i - 1] - budget[i - 1]) / 100) * 100;
    }
    total *= 1.2;
    return std::to_string(left[12] + total);
}

int main() {
    std::vector<int> budget{100, 290, 200, 120, 100, 90, 150, 200, 350, 210, 180, 260};
    std::cout << solve(budget) << std::endl;
    return 0;
}