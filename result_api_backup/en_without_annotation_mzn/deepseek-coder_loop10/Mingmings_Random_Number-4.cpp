#include <iostream>
#include <vector>
#include <set>
#include <algorithm>

int main() {
    int n;
    std::cin >> n;
    std::vector<int> random(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> random[i];
    }

    std::set<int> random_set(random.begin(), random.end());
    int num = random_set.size();

    std::vector<int> out(random_set.begin(), random_set.end());

    std::cout << num << std::endl;
    for (int i = 0; i < num; ++i) {
        std::cout << out[i] << " ";
    }
    std::cout << std::endl;

    return 0;
}