#include <iostream>
#include <string>
#include <unordered_map>
#include <cmath>

bool isPrime(int num) {
    if (num <= 1) return false;
    if (num == 2) return true;
    if (num % 2 == 0) return false;
    for (int i = 3; i <= std::sqrt(num); i += 2) {
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
        if (pair.second > maxn) maxn = pair.second;
        if (pair.second < minn) minn = pair.second;
    }

    int diff = maxn - minn;
    if (isPrime(diff)) {
        std::cout << "Lucky Word\n" << diff << std::endl;
    } else {
        std::cout << "No Answer\n0" << std::endl;
    }

    return 0;
}
