#include <iostream>
#include <string>
#include <algorithm>

int main() {
    std::string s;
    std::cin >> s;
    
    bool isNegative = (s[0] == '-');
    if (isNegative) {
        s = s.substr(1);
    }
    
    std::reverse(s.begin(), s.end());
    
    size_t start = 0;
    while (start < s.size() && s[start] == '0') {
        ++start;
    }
    
    if (start == s.size()) {
        std::cout << "0";
    } else {
        if (isNegative) {
            std::cout << "-";
        }
        std::cout << s.substr(start);
    }
    
    return 0;
}