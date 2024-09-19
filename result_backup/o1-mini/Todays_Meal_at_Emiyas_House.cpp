#include <iostream>
#include <vector>
#include <cstring>
using namespace std;

typedef long long ll;

const int MOD = 998244353;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n, m;
    cin >> n >> m;
    // Initialize a[i][j]
    vector<vector<int>> a(n, vector<int>(m, 0));
    for(int i=0;i<n;i++) {
        for(int j=0;j<m;j++) {
            cin >> a[i][j];
        }
    }
    // Precompute c[j][t] for all j and t up to 50
    // c[j][t] stores the number of ways to choose t dishes from ingredient j
    // with distinct cooking methods
    vector<vector<int>> c(m, vector<int>(51, 0));
    for(int j=0;j<m;j++){
        c[j][0] = 1;
        for(int i=0;i<n;i++){
            if(a[i][j] ==0) continue;
            for(int t=50; t>=1; t--){
                c[j][t] = (int)((c[j][t] + (ll)c[j][t-1] * a[i][j]) % MOD);
            }
        }
    }
    ll answer =0;
    // For each k from1 to n
    for(int k=1; k<=n; k++){
        int b = k /2;
        // Initialize DP
        vector<int> dp(k+1, 0);
        dp[0] =1;
        // Iterate over all m ingredients
        for(int j=0; j<m; j++){
            // For each j, iterate t from1 to min(b,50)
            int max_t = b;
            if(max_t >50) max_t =50;
            for(int t=1; t<=max_t; t++){
                if(c[j][t]==0) continue;
                for(int s=k; s>=t; s--){
                    dp[s] = (int)((dp[s] + (ll)dp[s - t] * c[j][t]) % MOD);
                }
            }
        }
        answer = (answer + dp[k]) % MOD;
    }
    cout << answer;
}