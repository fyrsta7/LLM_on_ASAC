#include <iostream>
#include <vector>
#include <map>

int main() {
    int n;
    std::cin >> n;
    std::map<long long, int> frequency;
    for(int i = 0; i < n; ++i) {
        long long num;
        std::cin >> num;
        ++frequency[num];
    }

    for(const auto& entry : frequency) {
        std::cout << entry.first << " " << entry.second << std::endl;
    }
    
    return 0;
}