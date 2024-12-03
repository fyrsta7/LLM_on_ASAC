#include <iostream>
#include <vector>
#include <climits>

int main() {
    int n;
    std::cin >> n;
    
    std::vector<int> h(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> h[i];
    }
    
    std::vector<int> state(n, 0);
    int actions = 0;
    
    auto build = [&](int left, int right) {
        for (int i = left; i <= right; ++i) {
            state[i]++;
        }
    };
    
    for (int i = 0; i < n; ++i) {
        while (state[i] < h[i]) {
            int j = i;
            while (j < n && state[j] < h[j]) {
                j++;
            }
            build(i, j - 1);
            actions++;
        }
    }
    
    std::cout << actions << std::endl;
    
    return 0;
}