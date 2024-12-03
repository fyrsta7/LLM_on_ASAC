#include <iostream>
#include <vector>

int main() {
    int n, k;
    std::cin >> n >> k;

    std::vector<int> grayCode(n, 0);
    for (int i = 0; i < n; ++i) {
        grayCode[i] = (k >> i) ^ (k >> (i + 1));
    }

    for (int i = n - 1; i >= 0; --i) {
        std::cout << grayCode[i];
    }
    std::cout << std::endl;

    return 0;
}
