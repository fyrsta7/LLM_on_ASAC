#include <iostream>
#include <vector>
#include <cstring>

using namespace std;

const int MOD = 1000007;

int countArrangements(int n, int m, vector<int>& a) {
    vector<int> dp(m + 1, 0);
    dp[0] = 1; // There's one way to arrange zero flowers

    for (int i = 0; i < n; i++) {
        for (int j = m; j >= 0; j--) {
            for (int k = 1; k <= a[i] && j >= k; k++) {
                dp[j] = (dp[j] + dp[j - k]) % MOD;
            }
        }
    }
    
    return dp[m];
}

int main() {
    int n, m;
    cin >> n >> m;
    vector<int> a(n);
    
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    
    cout << countArrangements(n, m, a) << endl;
    return 0;
}