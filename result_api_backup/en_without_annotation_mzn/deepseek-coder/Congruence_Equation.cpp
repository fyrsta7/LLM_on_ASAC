#include <iostream>
#include <numeric>

int main() {
    int a, b;
    std::cin >> a >> b;

    int x = 1;
    while ((a * x) % b != 1) {
        x++;
    }

    std::cout << x << std::endl;
    return 0;
}