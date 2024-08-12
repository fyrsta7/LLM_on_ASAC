#include <iostream>

using namespace std;

long long extended_gcd(long long a, long long b, long long &x, long long &y) {
    if (b == 0) {
        x = 1;
        y = 0;
        return a;
    }
    long long x1, y1;
    long long gcd = extended_gcd(b, a % b, x1, y1);
    x = y1;
    y = x1 - (a / b) * y1;
    return gcd;
}

int main() {
    long long a, b;
    cin >> a >> b;
    long long x, y;
    extended_gcd(a, b, x, y);
    x = (x % b + b) % b; // Ensure x is positive
    cout << x << endl;
    return 0;
}