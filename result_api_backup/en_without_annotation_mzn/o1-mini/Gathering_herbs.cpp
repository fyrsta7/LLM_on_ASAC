#include<bits/stdc++.h>
using namespace std;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    int T, M;
    cin >> T >> M;
    vector<pair<int, int>> herbs(M);
    for(auto &p: herbs) cin >> p.first >> p.second;
    // Initialize DP
    vector<int> dp(T+1, 0);
    for(auto &[cost, total]: herbs){
        for(int t = T; t >= cost; t--){
            if(dp[t - cost] + total > dp[t]){
                dp[t] = dp[t - cost] + total;
            }
        }
    }
    int answer = 0;
    for(int t=0;t<=T;t++) answer = max(answer, dp[t]);
    cout << answer;
}