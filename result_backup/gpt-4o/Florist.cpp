#include <iostream>
#include <vector>
#include <algorithm>

int getMaxFlowers(const std::vector<int>& heights) {
    int n = heights.size();
    if (n == 1) return 1;

    std::vector<int> dp_inc(n, 1);
    std::vector<int> dp_dec(n, 1);

    for (int i = 1; i < n; ++i) {
        if (i > 1 && heights[i] > heights[i - 2])
            dp_inc[i] = dp_inc[i - 2] + 1;
        if (heights[i] > heights[i - 1])
            dp_inc[i] = std::max(dp_inc[i], dp_inc[i - 1] + 1);
        
        if (i > 1 && heights[i] < heights[i - 2])
            dp_dec[i] = dp_dec[i - 2] + 1;
        if (heights[i] < heights[i - 1])
            dp_dec[i] = std::max(dp_dec[i], dp_dec[i - 1] + 1);
    }

    return std::max(*std::max_element(dp_inc.begin(), dp_inc.end()), *std::max_element(dp_dec.begin(), dp_dec.end()));
}

int main() {
    int n;
    std::cin >> n;
    std::vector<int> heights(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> heights[i];
    }

    std::cout << getMaxFlowers(heights) << std::endl;

    return 0;
}