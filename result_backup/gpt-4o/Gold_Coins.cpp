#include <iostream>

int main() {
    int K;
    std::cin >> K;

    int totalCoins = 0;
    int coinsPerDay = 1;
    int daysCount = 1;

    while (K > 0) {
        if (K >= daysCount) {
            totalCoins += coinsPerDay * daysCount;
            K -= daysCount;
        } else {
            totalCoins += coinsPerDay * K;
            K = 0;
        }
        coinsPerDay += 1;
        daysCount += 1;
    }

    std::cout << totalCoins << std::endl;
    return 0;
}