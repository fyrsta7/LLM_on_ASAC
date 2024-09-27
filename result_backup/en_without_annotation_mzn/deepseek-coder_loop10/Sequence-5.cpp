#include <iostream>
#include <cmath>

int main() {
    int k, N;
    std::cin >> k >> N;

    int l = std::ceil(std::log2(N));
    int ans = 0;

    for (int i = 0; i < l; ++i) {
        if (N & (1 << i)) {
            ans += std::pow(k, i);
        }
    }

    std::cout << ans << std::endl;
    return 0;
}
