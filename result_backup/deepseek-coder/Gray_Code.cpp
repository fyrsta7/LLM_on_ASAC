#include <iostream>
#include <vector>
#include <string>

std::string toBinaryString(unsigned long long num, int n) {
    std::string result;
    for (int i = n - 1; i >= 0; --i) {
        result += ((num >> i) & 1) ? '1' : '0';
    }
    return result;
}

std::string grayCode(int n, unsigned long long k) {
    if (n == 1) {
        return (k == 0) ? "0" : "1";
    }
    unsigned long long mid = 1ULL << (n - 1);
    if (k < mid) {
        return "0" + grayCode(n - 1, k);
    } else {
        return "1" + grayCode(n - 1, mid - 1 - (k - mid));
    }
}

int main() {
    int n;
    unsigned long long k;
    std::cin >> n >> k;
    std::cout << grayCode(n, k) << std::endl;
    return 0;
}
