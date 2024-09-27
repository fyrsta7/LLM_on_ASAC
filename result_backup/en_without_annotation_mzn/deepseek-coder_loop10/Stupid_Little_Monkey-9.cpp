#include <iostream>
#include <string>
#include <algorithm>
#include <unordered_map>

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

    std::unordered_map<char, int> freq;
    for (char c : str) {
        freq[c]++;
    }

    int maxn = 0, minn = str.size();
    for (const auto& pair : freq) {
        maxn = std::max(maxn, pair.second);
        minn = std::min(minn, pair.second);
    }

    int diff = maxn - minn;
    if (isPrime(diff)) {
        std::cout << "Lucky Word\n" << diff << std::endl;
    } else {
        std::cout << "No Answer\n0" << std::endl;
    }

    return 0;
}
