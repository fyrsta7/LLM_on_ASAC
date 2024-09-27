#include <iostream>
#include <cmath>

int main() {
    int n;
    std::cin >> n;
    
    int m = 2;
    for (int i = 2; i <= std::sqrt(n); ++i) {
        if (n % i == 0) {
            m = i;
        }
    }
    
    std::cout << m << std::endl;
    return 0;
}