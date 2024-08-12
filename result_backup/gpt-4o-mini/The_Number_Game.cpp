#include <iostream>
#include <string>

int main() {
    std::string s;
    std::cin >> s;
    int count = 0;
    
    for (char c : s) {
        if (c == '1') {
            count++;
        }
    }
    
    std::cout << count << std::endl;
    return 0;
}