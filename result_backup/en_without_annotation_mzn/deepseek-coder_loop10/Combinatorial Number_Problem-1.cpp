#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

const int MAXN = 100000;
const int MAXK = 1000000;

int factorial_mod[MAXN + 1][MAXK];

void precompute_factorials(int K) {
    factorial_mod[0][0] = 1;
    for (int i = 1; i <= MAXN; ++i) {
        factorial_mod[i][0] = 1;
        for (int j = 1; j < K; ++j) {
            factorial_mod[i][j] = (factorial_mod[i - 1][j] * i) % K;
        }
    }
}

int count_binomial_mod_zero(int n, int m, int K) {
    int count = 0;
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= min(i, m); ++j) {
            int binomial_coefficient = factorial_mod[i][K - 1] / (factorial_mod[j][K - 1] * factorial_mod[i - j][K - 1]);
            if (binomial_coefficient % K == 0) {
                ++count;
            }
        }
    }
    return count;
}

int main() {
    int T, K;
    cin >> T >> K;
    vector<int> n(T), m(T);
    for (int i = 0; i < T; ++i) {
        cin >> n[i] >> m[i];
    }

    precompute_factorials(K);

    vector<int> ans(T);
    for (int t = 0; t < T; ++t) {
        ans[t] = count_binomial_mod_zero(n[t], m[t], K);
    }

    for (int t = 0; t < T; ++t) {
        cout << ans[t] << endl;
    }

    return 0;
}
