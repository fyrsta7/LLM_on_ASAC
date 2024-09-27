#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>

int main() {
    int n;
    std::cin >> n;
    std::vector<int> number(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> number[i];
    }

    std::unordered_map<int, int> count_map;
    for (int num : number) {
        count_map[num]++;
    }

    std::vector<std::pair<int, int>> count_num;
    for (const auto& pair : count_map) {
        count_num.emplace_back(pair.first, pair.second);
    }

    std::sort(count_num.begin(), count_num.end());

    for (const auto& pair : count_num) {
        std::cout << pair.first << " " << pair.second << "\n";
    }

    return 0;
}