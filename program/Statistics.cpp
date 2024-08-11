#include <iostream>

int countOccurrencesOfTwo(int n) {
    int count = 0;
    while (n > 0) {
        if (n % 10 == 2) {
            count++;
        }
        n /= 10;
    }
    return count;
}

int main() {
    int L, R;
    std::cin >> L >> R;
    
    int count = 0;
    for (int i = L; i <= R; i++) {
        count += countOccurrencesOfTwo(i);
    }
    
    std::cout << count << std::endl;
    
    return 0;
}