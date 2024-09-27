#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

const int MAXN = 1000005;
const int MOD = 1000000007;

vector<int> fact(MAXN);
vector<int> inv_fact(MAXN);

int mod_pow(int base, int exp, int mod) {
    int result = 1;
    while (exp > 0) {
        if (exp % 2 == 1) result = (1LL * result * base) % mod;
        base = (1LL * base * base) % mod;
        exp /= 2;
    }
    return result;
}

void precompute_factorials(int max_n, int mod) {
    fact[0] = 1;
    for (int i = 1; i <= max_n; ++i) {
        fact[i] = (1LL * fact[i - 1] * i) % mod;
    }
    inv_fact[max_n] = mod_pow(fact[max_n], mod - 2, mod);
    for (int i = max_n - 1; i >= 0; --i) {
        inv_fact[i] = (1LL * inv_fact[i + 1] * (i + 1)) % mod;
    }
}

int binomial_coefficient(int n, int k, int mod) {
    if (k > n || k < 0) return 0;
    return (1LL * fact[n] * ((1LL * inv_fact[k] * inv_fact[n - k]) % mod)) % mod;
}

int main() {
    int T, K;
    cin >> T >> K;
    vector<int> n(T), m(T);
    for (int i = 0; i < T; ++i) {
        cin >> n[i] >> m[i];
    }

    precompute_factorials(MAXN - 1, K);

    vector<int> ans(T);
    for (int t = 0; t < T; ++t) {
        int count = 0;
        for (int i = 1; i <= n[t]; ++i) {
            for (int j = 1; j <= m[t] && j <= i; ++j) {
                if (binomial_coefficient(i, j, K) == 0) {
                    count++;
                }
            }
        }
        ans[t] = count;
    }

    for (int i = 0; i < T; ++i) {
        cout << ans[i] << endl;
    }

    return 0;
}