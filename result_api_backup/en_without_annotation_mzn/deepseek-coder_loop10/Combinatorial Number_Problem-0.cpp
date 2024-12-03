#include <iostream>
#include <vector>
using namespace std;

const int MAXN = 100000;
const int MOD = 1000000007;

vector<int> factorial(MAXN + 1, 1);
vector<int> inv_factorial(MAXN + 1, 1);

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
    for (int i = 2; i <= max_n; ++i) {
        factorial[i] = (1LL * factorial[i - 1] * i) % mod;
    }
    inv_factorial[max_n] = mod_pow(factorial[max_n], mod - 2, mod);
    for (int i = max_n - 1; i >= 1; --i) {
        inv_factorial[i] = (1LL * inv_factorial[i + 1] * (i + 1)) % mod;
    }
}

int binomial_coefficient(int n, int k, int mod) {
    if (k > n) return 0;
    return (1LL * factorial[n] * inv_factorial[k] % mod * inv_factorial[n - k] % mod);
}

int main() {
    int T, K;
    cin >> T >> K;
    vector<int> n(T), m(T);
    for (int i = 0; i < T; ++i) {
        cin >> n[i] >> m[i];
    }

    precompute_factorials(MAXN, MOD);

    vector<int> ans(T);
    for (int t = 0; t < T; ++t) {
        int count = 0;
        for (int i = 1; i <= n[t]; ++i) {
            for (int j = 1; j <= m[t] && j <= i; ++j) {
                if (binomial_coefficient(i, j, MOD) % K == 0) {
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
