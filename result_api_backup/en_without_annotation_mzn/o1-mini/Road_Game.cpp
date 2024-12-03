#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const ll NEG_INF = LLONG_MIN;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n, m, p;
    cin >> n >> m >> p;
    // coins[n][m]
    vector<vector<int>> coins(n, vector<int>(m));
    for(int i=0;i<n;i++) {
        for(int j=0;j<m;j++) {
            cin >> coins[i][j];
        }
    }
    // cost[n]
    vector<int> cost(n);
    for(int i=0;i<n;i++) cin >> cost[i];
    // DP[m+1]
    vector<ll> dp(m+1, NEG_INF);
    dp[0] = 0;
    for(int j=0; j<m; j++){
        if(dp[j] == NEG_INF) continue;
        for(int l=1; l<=p; l++){
            if(j + l > m) break;
            for(int s=1; s<=n; s++){
                ll sum_coins = 0;
                for(int x=1; x<=l; x++){
                    int loc = (s - 2 + x) % n +1;
                    int idx = j + x -1;
                    sum_coins += coins[loc-1][idx];
                }
                ll benefit = dp[j] + sum_coins - (ll)cost[s-1];
                if(benefit > dp[j+l]){
                    dp[j+l] = benefit;
                }
            }
        }
    }
    cout << dp[m] << "\n";
}