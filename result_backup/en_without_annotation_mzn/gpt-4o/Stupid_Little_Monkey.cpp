#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cmath>

bool is_prime(int num) {
    if (num <= 1) return false;
    if (num == 2) return true;
    if (num % 2 == 0) return false;
    for (int i = 3; i <= std::sqrt(num); i += 2) {
        if (num % i == 0) return false;
    }
    return true;
}

std::string solve(const std::string &str) {
    int n = str.size();
    std::vector<int> freq(256, 0);

    for (char c : str) {
        freq[c]++;
    }

    int maxn = *max_element(freq.begin(), freq.end());
    int minn = *min_element(freq.begin(), freq.end(), [](int a, int b) {
        return (a == 0 ? INT_MAX : a) < (b == 0 ? INT_MAX : b);
    });

    int diff = maxn - minn;
    if (is_prime(diff)) {
        return "Lucky Word\n" + std::to_string(diff);
    } else {
        return "No Answer\n0";
    }
}

int main() {
    std::string str;
    std::cin >> str;
    std::cout << solve(str) << std::endl;
    return 0;
}