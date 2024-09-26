#include <iostream>
#include <vector>

int main() {
    int n, x;
    std::cin >> n >> x;

    int ans = 0;
    std::vector<int> digitCount(10, 0);

    for (int i = 1; i <= n; ++i) {
        int num = i;
        while (num > 0) {
            digitCount[num % 10]++;
            num /= 10;
        }
    }

    ans = digitCount[x];
    std::cout << ans << std::endl;

    return 0;
}