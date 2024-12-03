#include <iostream>
#include <vector>
using namespace std;

const int MAXN = 2001;

// Precompute factorials and their modular inverses
long long factorial[MAXN], invFactorial[MAXN];
const int MOD = 1e9 + 7;

// Function to calculate power with modular arithmetic
long long modPow(long long base, long long exp, long long mod) {
    long long result = 1;
    while (exp > 0) {
        if (exp % 2 == 1)
            result = result * base % mod;
        base = base * base % mod;
        exp /= 2;
    }
    return result;
}

// Precompute factorials and inverse factorials
void precomputeFactorials() {
    factorial[0] = invFactorial[0] = 1;
    for (int i = 1; i < MAXN; ++i) {
        factorial[i] = factorial[i - 1] * i % MOD;
        invFactorial[i] = modPow(factorial[i], MOD - 2, MOD);
    }
}

// Function to compute nCr modulo MOD
long long nCr(int n, int r) {
    if (r > n)
        return 0;
    return factorial[n] * invFactorial[r] % MOD * invFactorial[n - r] % MOD;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    precomputeFactorials();
    
    int t, k;
    cin >> t >> k;
    
    while (t--) {
        int n, m;
        cin >> n >> m;
        
        int count = 0;
        for (int i = 0; i <= n; ++i) {
            for (int j = 0; j <= min(i, m); ++j) {
                if (nCr(i, j) % k == 0) {
                    ++count;
                }
            }
        }
        
        cout << count << '\n';
    }

    return 0;
}