#include <iostream>
#include <string>

int main() {
    std::string title;
    std::getline(std::cin, title);
    
    int answer = 0;
    for (char c : title) {
        if (c != ' ') {
            answer++;
        }
    }
    
    std::cout << answer << std::endl;
    return 0;
}