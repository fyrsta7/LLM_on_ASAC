#include <iostream>
#include <vector>
using namespace std;

const int MOD = 10007;

int modPow(int base, int exp, int mod) {
    int result = 1;
    base = base % mod;
    while (exp > 0) {
        if (exp % 2 == 1)
            result = (result * base) % mod;
        exp = exp >> 1;
        base = (base * base) % mod;
    }
    return result;
}

int modInverse(int num, int mod) {
    return modPow(num, mod - 2, mod);
}

int factorialMod(int n, int mod) {
    int result = 1;
    for (int i = 2; i <= n; ++i) {
        result = (result * i) % mod;
    }
    return result;
}

int combinatorialMod(int n, int k, int mod) {
    if (k > n) return 0;
    int numerator = factorialMod(n, mod);
    int denominator = (factorialMod(k, mod) * factorialMod(n - k, mod)) % mod;
    return (numerator * modInverse(denominator, mod)) % mod;
}

int main() {
    int a, b, k, n, m;
    cin >> a >> b >> k >> n >> m;

    int coefficient = (combinatorialMod(k, n, MOD) * modPow(a, n, MOD) % MOD * modPow(b, m, MOD) % MOD) % MOD;
    cout << coefficient << endl;

    return 0;
}