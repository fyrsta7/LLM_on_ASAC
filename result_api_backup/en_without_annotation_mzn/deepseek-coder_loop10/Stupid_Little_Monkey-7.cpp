#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

bool isPrime(int num) {
    if (num <= 1) return false;
    for (int i = 2; i * i <= num; ++i) {
        if (num % i == 0) return false;
    }
    return true;
}

int main() {
    std::string str;
    std::cin >> str;
    int n = str.length();

    std::vector<int> times(26, 0);
    for (char c : str) {
        ++times[c - 'a'];
    }

    int maxn = *std::max_element(times.begin(), times.end());
    int minn = *std::min_element(times.begin(), times.end(), [](int a, int b) {
        return a > 0 && (b == 0 || a < b);
    });

    int diff = maxn - minn;
    if (isPrime(diff)) {
        std::cout << "Lucky Word\n" << diff << std::endl;
    } else {
        std::cout << "No Answer\n0" << std::endl;
    }

    return 0;
}
