#include <iostream>
#include <vector>
#include <map>
#include <algorithm>

int main() {
    int n;
    std::cin >> n;
    std::vector<int> number(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> number[i];
    }

    std::map<int, int> count_map;
    for (int num : number) {
        count_map[num]++;
    }

    std::vector<std::pair<int, int>> count_num(count_map.begin(), count_map.end());
    for (const auto& pair : count_num) {
        std::cout << pair.first << " " << pair.second << std::endl;
    }

    return 0;
}