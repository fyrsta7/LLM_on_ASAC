#include <iostream>
#include <string>

int main() {
    std::string numstr;
    std::cin >> numstr;
    
    int one_num = 0;
    for (char c : numstr) {
        if (c == '1') {
            ++one_num;
        }
    }
    
    std::cout << one_num << std::endl;
    return 0;
}