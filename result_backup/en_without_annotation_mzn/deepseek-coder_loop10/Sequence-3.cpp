#include <iostream>
#include <cmath>

int main() {
    int k, N;
    std::cin >> k >> N;

    int ans = 0;
    int power = 1;

    while (N > 0) {
        if (N % 2 == 1) {
            ans += power;
        }
        power *= k;
        N /= 2;
    }

    std::cout << ans << std::endl;
    return 0;
}
