#include <iostream>
#include <cmath>

int main() {
    int n;
    std::cin >> n;
    int m = static_cast<int>(sqrt(n));
    while (n % m != 0) {
        --m;
    }
    std::cout << m << std::endl;
    return 0;
}
