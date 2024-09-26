#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <set>

int main() {
    int n, k;
    std::cin >> n >> k;
    int len = std::pow(10, k);
    std::vector<int> suffix(len + 1);
    suffix[1] = std::pow(n, 1) % len;
    
    for (int i = 2; i <= len; ++i) {
        suffix[i] = std::pow(n, i) % len;
    }
    
    int first_suffix = suffix[1];
    std::set<int> out_set;
    
    for (int i = 2; i <= len; ++i) {
        if (suffix[i] == first_suffix) {
            out_set.insert(i);
        }
    }

    if (out_set.empty()) {
        std::cout << -1 << std::endl;
    } else {
        std::cout << *out_set.begin() - 1 << std::endl;
    }

    return 0;
}