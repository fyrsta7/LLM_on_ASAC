#include <iostream>
#include <cmath>

int main() {
    int A, B, C;
    std::cin >> A >> B >> C;
    std::cout << static_cast<int>(floor(A * 0.2 + B * 0.3 + C * 0.5)) << std::endl;
    return 0;
}