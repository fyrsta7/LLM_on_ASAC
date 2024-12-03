#include <iostream>
#include <unordered_map>
#include <vector>
#include <algorithm>

int main() {
    int n;
    std::cin >> n;
    std::unordered_map<int, int> countMap;
  
    for (int i = 0; i < n; ++i) {
        int num;
        std::cin >> num;
        countMap[num]++;
    }
  
    std::vector<std::pair<int, int>> counts(countMap.begin(), countMap.end());
    std::sort(counts.begin(), counts.end());

    for (const auto& pair : counts) {
        std::cout << pair.first << " " << pair.second << std::endl;
    }

    return 0;
}