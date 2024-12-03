#include<bits/stdc++.h>
using namespace std;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    long long n, m;
    cin >> n >> m;
    vector<long long> V(m);
    vector<long long> P(m);
    for(auto &x: V) cin>>x;
    for(auto &x: P) cin>>x;
    vector<long long> dp(n+1, 0);
    for(int i=0;i<m;i++){
        long long vi = V[i];
        long long pi = P[i];
        long long value = vi * pi;
        for(long long w = n; w >= vi; w--){
            if(dp[w - vi] + value > dp[w]){
                dp[w] = dp[w - vi] + value;
            }
        }
    }
    long long res = 0;
    for(auto x: dp) if(x > res) res = x;
    cout << res << "\n";
}