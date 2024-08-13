#include <iostream>
using namespace std;

int reverseDigits(int n) {
    bool isNegative = n < 0;
    if (isNegative) n = -n;

    int reversedNumber = 0;
    while (n > 0) {
        reversedNumber = reversedNumber * 10 + n % 10;
        n /= 10;
    }

    return isNegative ? -reversedNumber : reversedNumber;
}

int main() {
    int n;
    cin >> n;
    cout << reverseDigits(n) << endl;
    return 0;
}