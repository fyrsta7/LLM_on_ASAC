#include <iostream>
using namespace std;

int main() {
    int K;
    cin >> K;

    long long totalGold = 0;
    int day = 1;
    int currentCoins = 1;
    
    while (K > 0) {
        int daysToEarn = currentCoins; 
        if (K < daysToEarn) {
            totalGold += (long long)currentCoins * K;
            break;
        } else {
            totalGold += (long long)currentCoins * daysToEarn;
            K -= daysToEarn;
            currentCoins++;
        }
    }
    
    cout << totalGold << endl;
    return 0;
}