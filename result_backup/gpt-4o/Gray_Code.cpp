#include <iostream>
#include <bitset>

std::string getGrayCode(int n, long long k) {
    long long grayCodeNumber = k ^ (k >> 1);
    return std::bitset<64>(grayCodeNumber).to_string().substr(64 - n);
}

int main() {
    int n;
    long long k;
    std::cin >> n >> k;

    std::string result = getGrayCode(n, k);
    std::cout << result << std::endl;

    return 0;
}