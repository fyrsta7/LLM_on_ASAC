#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

long long gcd(long long x, long long y) {
    while (y) {
        long long temp = y;
        y = x % y;
        x = temp;
    }
    return x;
}

long long lcm(long long x, long long y) {
    return (x / gcd(x, y)) * y;
}

int countDivisors(long long x) {
    int count = 0;
    for (long long i = 1; i * i <= x; ++i) {
        if (x % i == 0) {
            count++;
            if (i != (x / i)) count++;
        }
    }
    return count;
}

int main() {
    int n;
    cin >> n;
    while (n--) {
        long long a0, a1, b0, b1;
        cin >> a0 >> a1 >> b0 >> b1;

        long long d1 = a0 / a1; 
        long long d2 = b1 / b0; 

        if (d2 % d1 != 0) {
            cout << 0 << endl;
            continue;
        }

        long long k = d2 / d1; 
        long long x = a1 * k;

        long long g = lcm(b0, x) / b1; 
        long long m = x / a1; 
        long long l = (x * g) / x;

        long long total_divisors = countDivisors(gcd(l, m));
        cout << total_divisors << endl;
    }
    return 0;
}