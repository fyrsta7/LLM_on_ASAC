#include<bits/stdc++.h>
using namespace std;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n, m;
    cin >> n >> m;
    vector<int> A(n);
    for(auto &x:A) cin>>x;
    // Initialize DP
    vector<bool> dp(m+1, false);
    dp[0] = true;
    // To reconstruct
    vector<int> prev(m+1, -1);
    vector<int> used(m+1, -1);
    for(int i=0;i<n;i++){
        for(int s = m; s >=0; s--){
            if(dp[s]){
                int max_add = min(A[i], m - s);
                for(int k=1;k<=max_add;k++){
                    if(!dp[s+k]){
                        dp[s+k] = true;
                        prev[s+k] = i;
                        used[s+k] = k;
                    }
                }
            }
        }
    }
    if(!dp[m]){
        // No solution
        return 0;
    }
    // Reconstruct
    vector<int> B(n,0);
    int s = m;
    while(s >0){
        int i = prev[s];
        int k = used[s];
        B[i] = k;
        s -= k;
    }
    for(int i=0;i<n;i++) cout<<B[i]<<(i<n-1?" ":"\n");
}