```
#include <iostream>
#include <vector>
using namespace std;

int main() {
    int N, m;
    cin >> N >> m;
    
    vector<int> v(m+1), p(m+1), vp(m+1);
    for (int i = 1; i <= m; ++i) {
        cin >> v[i] >> p[i];
        vp[i] = v[i] * p[i];
    }
    
    vector<int> dp(N + 1, 0);
    
    for (int i = 1; i <= m; ++i) {
        for (int j = N; j >= v[i]; --j) {
            dp[j] = max(dp[j], dp[j - v[i]] + vp[i]);
        }
    }
    
    cout << dp[N] << endl;

    return 0;
}
