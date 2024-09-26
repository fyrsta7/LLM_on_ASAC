#include <iostream>

const int MOD = 10007;

// Function to compute (x^y) % p using iterative method
int power(int x, int y, int p) {
    int res = 1; // Initialize result
    x = x % p; // Update x if it is more than or equal to p
    while (y > 0) {
        if (y & 1) // If y is odd, multiply x with result
            res = (res * x) % p;
        y = y >> 1; // y = y/2
        x = (x * x) % p; // Change x to x^2
    }
    return res;
}

// Function to return gcd of a and b
int gcd(int a, int b) {
    if (b == 0)
        return a;
    return gcd(b, a % b);
}

// Function to perform modular division
int modInverse(int a, int p) {
    int g = gcd(a, p);
    if (g != 1) // In case a and p are not coprime
        return -1;
    else // If a and p are coprime
        return power(a, p - 2, p);
}

// Function to compute nCr % p using Fermat's Little Theorem
int nCrModPFermat(int n, int r, int p) {
    if (r == 0)
        return 1;
    int fac[n + 1];
    fac[0] = 1;
    // Precompute factorials
    for (int i = 1; i <= n; i++)
        fac[i] = fac[i - 1] * i % p;
    return (fac[n] * modInverse(fac[r], p) % p * modInverse(fac[n - r], p) % p) % p;
}

int main() {
    int a, b, k, n, m;
    std::cin >> a >> b >> k >> n >> m;

    // Calculate the binomial coefficient (k choose n)
    int binomialCoefficient = nCrModPFermat(k, n, MOD);

    // Calculate (a^n) % 10007 and (b^m) % 10007
    int aTerm = power(a, n, MOD);
    int bTerm = power(b, m, MOD);

    // Calculate the required coefficient
    int result = (binomialCoefficient * aTerm % MOD * bTerm % MOD) % MOD;

    // Output the result
    std::cout << result << std::endl;

    return 0;
}