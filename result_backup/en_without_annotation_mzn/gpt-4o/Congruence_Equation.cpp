#include <iostream>
#include <limits>

int findMinX(int a, int b) {
    for (int x = 1; x < b; ++x) {
        if ((a * x) % b == 1) {
            return x;
        }
    }
    return -1;
}

int main() {
    int a, b;
    std::cin >> a >> b;
    int result = findMinX(a, b);
    std::cout << result << std::endl;
    return 0;
}