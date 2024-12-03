#include <iostream>
#include <vector>

int main() {
    int n, k;
    std::cin >> n >> k;

    std::vector<int> result(n);
    k++;

    for (int i = 0; i < n; ++i) {
        result[n - 1 - i] = (k >> i) & 1;
    }

    for (int i = 0; i < n; ++i) {
        std::cout << result[i];
    }

    return 0;
}
