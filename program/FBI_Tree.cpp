#include <iostream>
#include <string>

void constructFBITree(std::string s, char nodeType) {
    if (s.length() == 1) {
        std::cout << nodeType;
        return;
    }

    int len = s.length() / 2;
    constructFBITree(s.substr(0, len), nodeType); 
    constructFBITree(s.substr(len), nodeType == 'F' ? 'B' : 'I');
    std::cout << nodeType;
}

int main() {
    int N;
    std::cin >> N;
    std::string s;
    std::cin >> s;

    constructFBITree(s, s[0]);
    std::cout << std::endl;

    return 0;
}