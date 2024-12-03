#include <iostream>
using namespace std;

const int MOD = 10007;

int power(int base, int exp, int mod) {
    int result = 1;
    while (exp > 0) {
        if (exp % 2 == 1) {
            result = (result * base) % mod;
        }
        base = (base * base) % mod;
        exp /= 2;
    }
    return result;
}

int modInverse(int a, int mod) {
    return power(a, mod - 2, mod);
}

int binomialCoefficient(int n, int k, int mod) {
    if (k > n) return 0;
    int numerator = 1, denominator = 1;
    for (int i = 0; i < k; ++i) {
        numerator = (numerator * (n - i)) % mod;
        denominator = (denominator * (i + 1)) % mod;
    }
    return (numerator * modInverse(denominator, mod)) % mod;
}

int main() {
    int a, b, k, n, m;
    cin >> a >> b >> k >> n >> m;

    int coefficient = binomialCoefficient(k, n, MOD);
    coefficient = (coefficient * power(a, n, MOD)) % MOD;
    coefficient = (coefficient * power(b, m, MOD)) % MOD;

    cout << coefficient << endl;
    return 0;
}
