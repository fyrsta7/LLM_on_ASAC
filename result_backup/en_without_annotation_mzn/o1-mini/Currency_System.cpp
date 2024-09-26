#include <bits/stdc++.h>
using namespace std;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    int T;
    cin>>T;
    long long sum_m=0;
    while(T--){
        int n;
        cin>>n;
        vector<int>a(n);
        for(auto &x:a) cin>>x;
        sort(a.begin(), a.end());
        int m=0;
        int max_sum = accumulate(a.begin(), a.end(), 0);
        vector<bool> dp(max_sum+1, false);
        dp[0] = true;
        for(auto x:a){
            if(x > max_sum || !dp[x]){
                m++;
                for(int i=max_sum; i>=x; i--){
                    if(dp[i - x]) dp[i] = true;
                }
            }
        }
        sum_m += m;
    }
    cout<<sum_m;
}