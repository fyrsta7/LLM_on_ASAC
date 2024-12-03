#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

int N, m1, m2;
vector<int> S;
int max_T = 10000;
int M;

int mod_pow(int base, int exp, int mod) {
    int result = 1;
    while (exp > 0) {
        if (exp % 2 == 1) result = (result * base) % mod;
        base = (base * base) % mod;
        exp /= 2;
    }
    return result;
}

int find_min_time(int s) {
    for (int t = 1; t <= max_T; ++t) {
        if (mod_pow(s, t, M) == 0) return t;
    }
    return max_T;
}

int main() {
    cin >> N >> m1 >> m2;
    S.resize(N);
    for (int i = 0; i < N; ++i) cin >> S[i];
    M = pow(m1, m2);

    int ans = max_T;
    for (int i = 0; i < N; ++i) {
        ans = min(ans, find_min_time(S[i]));
    }

    if (ans == max_T) cout << "-1" << endl;
    else cout << ans << endl;

    return 0;
}
