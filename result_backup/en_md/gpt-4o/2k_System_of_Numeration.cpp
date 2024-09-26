#include <iostream>
#include <vector>
using namespace std;

int main() {
    int k, w;
    cin >> k >> w;
    int segments = (w + k - 1) / k;
    if (segments < 2) {
        cout << 0 << endl;
        return 0;
    }
    
    int base = 1 << k; // 2^k
    vector<vector<long long>> dp(segments, vector<long long>(base));

    for (int i = 1; i < base; ++i) {
        dp[0][i] = 1;
    }

    for (int len = 1; len < segments; ++len) {
        for (int j = 1; j < base; ++j) {
            dp[len][j] = 0;
            for (int p = j - 1; p >= 0; --p) {
                dp[len][j] += dp[len-1][p];
            }
        }
    }

    long long result = 0;
    for (int i = 1; i < base; ++i) {
        result += dp[segments-1][i];
    }

    cout << result << endl;
    return 0;
}