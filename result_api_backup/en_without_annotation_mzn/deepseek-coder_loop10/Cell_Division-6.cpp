#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

int mod_exp(int base, int exp, int mod) {
    int result = 1;
    while (exp > 0) {
        if (exp % 2 == 1) result = (result * base) % mod;
        base = (base * base) % mod;
        exp /= 2;
    }
    return result;
}

int main() {
    int N, m1, m2;
    cin >> N >> m1 >> m2;
    vector<int> S(N);
    for (int i = 0; i < N; ++i) cin >> S[i];

    int M = pow(m1, m2);
    int max_T = 10000;
    int ans = max_T;

    for (int i = 0; i < N; ++i) {
        for (int t = 1; t <= max_T; ++t) {
            if (mod_exp(S[i], t, M) == 0) {
                ans = min(ans, t);
                break;
            }
        }
    }

    if (ans == max_T) cout << "-1" << endl;
    else cout << ans << endl;

    return 0;
}
