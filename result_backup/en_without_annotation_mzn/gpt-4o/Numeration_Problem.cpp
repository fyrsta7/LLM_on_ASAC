#include <iostream>

int appear_times(int num, int a) {
    if (num < 10) {
        return (num == a) ? 1 : 0;
    }
    return appear_times(num / 10, a) + ((num % 10) == a ? 1 : 0);
}

int main() {
    int n, x;
    std::cin >> n >> x;
    int ans = 0;
    for (int i = 1; i <= n; ++i) {
        ans += appear_times(i, x);
    }
    std::cout << ans << std::endl;
    return 0;
}