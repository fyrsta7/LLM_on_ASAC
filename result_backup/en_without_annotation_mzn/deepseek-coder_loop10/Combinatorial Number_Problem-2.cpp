#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

const int MAXN = 1000000;
vector<int> factorial(MAXN + 1, 1);
vector<int> factorial_inv(MAXN + 1, 1);
vector<int> inv(MAXN + 1, 1);

void precompute(int K) {
    for (int i = 2; i <= MAXN; ++i) {
        factorial[i] = 1LL * factorial[i - 1] * i % K;
        inv[i] = 1LL * (K - K / i) * inv[K % i] % K;
        factorial_inv[i] = 1LL * factorial_inv[i - 1] * inv[i] % K;
    }
}

int binomial_mod_k(int n, int k, int K) {
    if (k > n || k < 0) return 0;
    return 1LL * factorial[n] * factorial_inv[k] % K * factorial_inv[n - k] % K;
}

int main() {
    int T, K;
    cin >> T >> K;
    vector<int> n(T), m(T);
    for (int i = 0; i < T; ++i) cin >> n[i] >> m[i];

    precompute(K);

    vector<int> ans(T);
    for (int t = 0; t < T; ++t) {
        for (int i = 1; i <= n[t]; ++i) {
            for (int j = 1; j <= m[t] && j <= i; ++j) {
                if (binomial_mod_k(i, j, K) == 0) {
                    ans[t]++;
                }
            }
        }
    }

    for (int t = 0; t < T; ++t) {
        cout << ans[t] << endl;
    }

    return 0;
}
