#include <iostream>
#include <vector>
#include <string>

int main() {
    int n, m;
    std::cin >> n >> m;
    
    std::vector<int> face(n);
    std::vector<std::string> person(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> face[i] >> person[i];
    }
    
    std::vector<std::pair<int, int>> instruction(m);
    for (int i = 0; i < m; ++i) {
        std::cin >> instruction[i].first >> instruction[i].second;
    }
    
    int current_position = 0;
    for (int i = 0; i < m; ++i) {
        if ((face[current_position] == 0 && instruction[i].first == 0) || 
            (face[current_position] == 1 && instruction[i].first == 1)) {
            current_position = (current_position + n - instruction[i].second - 1) % n;
        } else {
            current_position = (current_position + instruction[i].second) % n;
        }
    }
    
    std::cout << person[current_position] << std::endl;
    
    return 0;
}
