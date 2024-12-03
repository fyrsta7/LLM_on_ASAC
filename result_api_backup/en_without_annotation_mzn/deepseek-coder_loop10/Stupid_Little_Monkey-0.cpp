#include <iostream>
#include <string>
#include <algorithm>
#include <vector>

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
    
    std::vector<int> count(26, 0);
    for (char c : str) {
        count[c - 'a']++;
    }
    
    int maxn = *std::max_element(count.begin(), count.end());
    int minn = *std::min_element(count.begin(), count.end());
    
    int diff = maxn - minn;
    if (isPrime(diff)) {
        std::cout << "Lucky Word\n" << diff << std::endl;
    } else {
        std::cout << "No Answer\n0" << std::endl;
    }
    
    return 0;
}
