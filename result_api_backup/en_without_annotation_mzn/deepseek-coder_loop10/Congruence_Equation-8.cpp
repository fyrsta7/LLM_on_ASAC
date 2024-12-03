#include <iostream>
#include <numeric>

int main() {
    int a, b;
    std::cin >> a >> b;

    for (int x = 1; ; ++x) {
        if ((a * x) % b == 1) {
            std::cout << x << std::endl;
            break;
        }
    }

    return 0;
}