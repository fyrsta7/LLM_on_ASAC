#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_set>

int main() {
    int n;
    std::cin >> n;
    std::vector<int> random(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> random[i];
    }

    std::unordered_set<int> random_set(random.begin(), random.end());
    std::vector<int> unique_elements(random_set.begin(), random_set.end());
    std::sort(unique_elements.begin(), unique_elements.end());

    int num = unique_elements.size();
    std::cout << num << std::endl;
    for (int i = 0; i < num; ++i) {
        std::cout << unique_elements[i] << " ";
    }
    std::cout << std::endl;

    return 0;
}