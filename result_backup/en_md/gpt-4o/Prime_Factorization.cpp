#include <iostream>
#include <cmath>
using namespace std;

bool isPrime(int num) {
    if (num <= 1) return false;
    if (num <= 3) return true;
    if (num % 2 == 0 || num % 3 == 0) return false;
    for (int i = 5; i * i <= num; i += 6) {
        if (num % i == 0 || num % (i + 2) == 0) return false;
    }
    return true;
}

int main() {
    int n;
    cin >> n;
    int largerPrime = 0;
    for (int i = 2; i <= sqrt(n); ++i) {
        if (n % i == 0) {
            int otherFactor = n / i;
            if (isPrime(i) && isPrime(otherFactor)) {
                largerPrime = max(i, otherFactor);
                break;
            }
        }
    }
    cout << largerPrime << endl;
    return 0;
}