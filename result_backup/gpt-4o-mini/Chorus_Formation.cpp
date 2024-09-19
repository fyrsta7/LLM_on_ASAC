#include <iostream>
#include <vector>
#include <algorithm>

int main() {
    int n;
    std::cin >> n;
    std::vector<int> heights(n);
    
    for (int i = 0; i < n; ++i) {
        std::cin >> heights[i];
    }
    
    std::vector<int> dp(n, 1); // dp[i] will hold the length of the longest sequence ending at index i

    // Find the longest increasing subsequence
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < i; ++j) {
            if (heights[j] < heights[i]) {
                dp[i] = std::max(dp[i], dp[j] + 1);
            }
        }
    }

    int max_increasing = *std::max_element(dp.begin(), dp.end());
    int min_out = n - max_increasing; // Minimum students to step out

    std::cout << min_out << std::endl;
    return 0;
}