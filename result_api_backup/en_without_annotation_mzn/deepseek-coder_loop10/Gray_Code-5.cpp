#include <iostream>
#include <vector>

void generateGrayCode(int n, int k) {
    std::vector<int> grayCode(n);
    for (int i = 0; i < n; ++i) {
        grayCode[i] = (k >> i) & 1;
    }
    for (int i = 0; i < n; ++i) {
        std::cout << grayCode[i];
    }
    std::cout << std::endl;
}

int main() {
    int n, k;
    std::cin >> n >> k;
    generateGrayCode(n, k);
    return 0;
}
