#include <iostream>
#include <string>

int main() {
    std::string s;
    std::getline(std::cin, s);
    int count = 0;

    for (char c : s) {
        if (c != ' ' && c != '\n') {
            count++;
        }
    }

    std::cout << count << std::endl;
    return 0;
}