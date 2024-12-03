#include <iostream>
#include <vector>
#include <algorithm>

int main() {
    int w, n;
    std::cin >> w >> n;
    std::vector<int> prices(n);

    for (int i = 0; i < n; ++i) {
        std::cin >> prices[i];
    }

    std::sort(prices.begin(), prices.end());

    int left = 0, right = n - 1, groups = 0;

    while (left <= right) {
        if (prices[left] + prices[right] <= w) {
            left++;
        }
        right--;
        groups++;
    }

    std::cout << groups << std::endl;
    return 0;
}