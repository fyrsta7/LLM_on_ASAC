#include <iostream>
#include <cmath>
#include <vector>

int main() {
    int k, N;
    std::cin >> k >> N;

    int l = std::ceil(std::log2(N));
    std::vector<int> idx(l, 0);
    int tempN = N;
    
    for (int i = 0; i < l && tempN > 0; ++i) {
        idx[i] = tempN % 2;
        tempN /= 2;
    }

    int ans = 0;
    for (int i = 0; i < l; ++i) {
        if (idx[i] == 1) {
            ans += std::pow(k, i);
        }
    }

    std::cout << ans << std::endl;
    return 0;
}