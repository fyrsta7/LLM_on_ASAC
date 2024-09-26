#include <iostream>
#include <string>
#include <algorithm>

int reverseInteger(int N) {
    bool isNegative = N < 0;
    N = std::abs(N);
    
    std::string str = std::to_string(N);
    std::reverse(str.begin(), str.end());
    
    int reversedNumber = std::stoi(str);
    return isNegative ? -reversedNumber : reversedNumber;
}

int main() {
    int N;
    std::cin >> N;
    std::cout << reverseInteger(N) << std::endl;
    return 0;
}