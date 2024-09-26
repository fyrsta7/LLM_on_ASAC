#include <iostream>
using namespace std;

int gcd(int a, int b) {
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

int main() {
    int a, b;
    cin >> a >> b;
    if (gcd(a, b) != 1) {
        cout << "Input denominations are not coprime." << endl;
        return 1;
    }
    cout << a * b - a - b << endl;
    return 0;
}
