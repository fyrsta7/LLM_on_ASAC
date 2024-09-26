#include <iostream>
#include <vector>

int main() {
    int n;
    std::cin >> n;

    std::vector<int> give(n + 1, 0);
    for (int i = 1; i <= n; ++i) {
        give[i] = i;
    }

    long long total = 0;
    for (int i = 1; i <= n; ++i) {
        total += give[i];
    }

    std::cout << total << std::endl;
    return 0;
}