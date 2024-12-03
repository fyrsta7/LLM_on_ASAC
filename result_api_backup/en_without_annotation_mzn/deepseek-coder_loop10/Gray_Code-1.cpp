#include <iostream>
#include <vector>

int main() {
    int n, k;
    std::cin >> n >> k;

    std::vector<int> grayCode(n, 0);
    k++; // Adjust k to 1-based index

    for (int i = 0; i < n; ++i) {
        grayCode[i] = (k >> (n - i - 1)) & 1;
    }

    for (int i = 0; i < n; ++i) {
        std::cout << grayCode[i];
    }

    return 0;
}
