#include <iostream>
#include <vector>

const int MOD = 10007;

// Function to compute the factorial modulo MOD
int factorial(int n) {
    if (n == 0) return 1;
    int result = 1;
    for (int i = 1; i <= n; ++i) {
        result = (result * i) % MOD;
    }
    return result;
}

// Function to compute the modular inverse of a under modulo MOD
int modInverse(int a) {
    int m0 = MOD, y = 0, x = 1;
    if (MOD == 1) return 0;

    while (a > 1) {
        int q = a / MOD;
        int t = MOD;

        MOD = a % MOD, a = t;
        t = y;

        y = x - q * y;
        x = t;
    }
    if (x < 0) x += m0;

    return x;
}

// Function to compute nCr % MOD
int nCr(int n, int r) {
    if (r > n) return 0;
    if (r == 0 || r == n) return 1;
    
    return (factorial(n) * modInverse(factorial(r)) % MOD * modInverse(factorial(n - r)) % MOD) % MOD;
}

int main() {
    int a, b, k, n, m;
    std::cin >> a >> b >> k >> n >> m;

    // Coefficient for (by + ax)^k
    int coeff = (nCr(k, n) * (std::pow(a, n) * std::pow(b, m)) % MOD) % MOD;
    
    std::cout << coeff << std::endl;
    return 0;
}