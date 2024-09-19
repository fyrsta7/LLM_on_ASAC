#include <iostream>
#include <vector>
using namespace std;

int main() {
    int N, m;
    cin >> N >> m;
    vector<int> v(m), p(m);
    for (int i = 0; i < m; ++i) {
        cin >> v[i] >> p[i];
    }

    vector<int> dp(N + 1, 0);
    for (int i = 0; i < m; ++i) {
        for (int j = N; j >= v[i]; --j) {
            dp[j] = max(dp[j], dp[j - v[i]] + v[i] * p[i]);
        }
    }

    cout << dp[N] << endl;
    return 0;
}
