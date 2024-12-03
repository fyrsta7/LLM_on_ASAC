#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>

int main() {
    int n;
    std::cin >> n;
    std::vector<int> number(n);
    std::unordered_map<int, int> count_map;

    for (int i = 0; i < n; ++i) {
        std::cin >> number[i];
        count_map[number[i]]++;
    }

    std::vector<std::pair<int, int>> count_num;
    for (const auto& item : count_map) {
        count_num.push_back(item);
    }

    std::sort(count_num.begin(), count_num.end());

    for (const auto& item : count_num) {
        std::cout << item.first << " " << item.second << "\n";
    }

    return 0;
}