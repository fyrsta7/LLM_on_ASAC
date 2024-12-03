#include <iostream>
#include <cmath>

int main() {
    int A, B, C;
    std::cin >> A >> B >> C;
    int result = std::floor(A * 0.2 + B * 0.3 + C * 0.5);
    std::cout << result << std::endl;
    return 0;
}