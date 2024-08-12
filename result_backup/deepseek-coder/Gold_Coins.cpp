#include <iostream>
using namespace std;

int main() {
    int K;
    cin >> K;
    
    long long totalCoins = 0;
    int day = 1;
    int coinsPerDay = 1;
    
    while (K > 0) {
        if (K >= day) {
            totalCoins += day * coinsPerDay;
            K -= day;
            day++;
            coinsPerDay++;
        } else {
            totalCoins += K * coinsPerDay;
            K = 0;
        }
    }
    
    cout << totalCoins << endl;
    return 0;
}