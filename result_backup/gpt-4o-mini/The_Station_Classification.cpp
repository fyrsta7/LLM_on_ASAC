#include <iostream>
#include <vector>
#include <set>

int main() {
    int n, m;
    std::cin >> n >> m;
    
    std::vector<std::set<int>> levels(n + 1);
    
    for (int i = 0; i < m; ++i) {
        int si;
        std::cin >> si;
        std::vector<int> stops(si);
        
        for (int j = 0; j < si; ++j) {
            std::cin >> stops[j];
        }
        
        for (int j = 0; j < si; ++j) {
            for (int k = stops[j]; k <= n; ++k) {
                levels[k].insert(i);
            }
        }
    }
    
    int distinctLevels = 0;
    
    for (int i = 1; i <= n; ++i) {
        if (!levels[i].empty()) {
            distinctLevels++;
        }
    }
    
    std::cout << distinctLevels << std::endl;

    return 0;
}