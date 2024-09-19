#include <iostream>
#include <vector>
using namespace std;

const int MOD = 1000007;

int main(){
    int n, m;
    cin >> n >> m;
    vector<int> a(n);
    for(int &x : a) cin >> x;
    if(m < n){
        cout << 0;
        return 0;
    }
    // Initialize DP table
    vector<vector<int>> dp(n+1, vector<int>(m+1, 0));
    dp[0][0] = 1;
    for(int i=1; i<=n; ++i){
        for(int j=0; j<=m; ++j){
            if(dp[i-1][j] ==0) continue;
            // Assign x_i from 1 to a[i-1]
            for(int k=1; k<=a[i-1] && j + k <=m; ++k){
                dp[i][j + k] = (dp[i][j + k] + dp[i-1][j]) % MOD;
            }
        }
    }
    // The answer is dp[n][m]
    cout << dp[n][m];
}