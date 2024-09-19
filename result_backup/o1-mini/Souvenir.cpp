#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    int T, N, M;
    cin >> T >> N >> M;
    // Prices are 1-based
    vector<vector<int>> P(T+1, vector<int>(N+1, 0));
    for(int t=1;t<=T;t++) {
        for(int j=1;j<=N;j++) {
            cin >> P[t][j];
        }
    }
    // Precompute next_max_day[j][t]
    vector<vector<int>> next_max_day(N+1, vector<int>(T+2, T+1));
    for(int j=1;j<=N;j++){
        int max_price = -1;
        int day = T+1;
        for(int t=T;t>=1;t--){
            if(P[t][j] > max_price){
                max_price = P[t][j];
                day = t;
            }
            next_max_day[j][t] = day;
        }
    }
    // Initialize dp
    // dp[t][m] = max coins at day t with m coins
    // Initialize all to -1
    vector<vector<int>> dp(T+2, vector<int>(10001, -1));
    dp[1][M] = M;
    for(int t=1;t<=T;t++){
        for(int m=0;m<=10000;m++){
            if(dp[t][m] == -1) continue;
            // Option1: do nothing, carry to t+1
            if(t+1 <= T){
                if(dp[t+1][m] < dp[t][m]){
                    dp[t+1][m] = dp[t][m];
                }
            }
            // Option2: for each j, buy and sell on next_max_day
            for(int j=1;j<=N;j++){
                int s = next_max_day[j][t];
                if(s == t || s > T) continue;
                if(P[s][j] <= P[t][j]) continue;
                if(P[t][j] ==0) continue;
                int k = m / P[t][j];
                if(k ==0) continue;
                int m_new = m % P[t][j] + k * P[s][j];
                if(m_new > 10000) m_new = 10000;
                if(dp[s][m_new] < m_new){
                    dp[s][m_new] = m_new;
                }
            }
        }
    }
    // On day T, must have all souvenirs sold, which is already handled
    // Find the maximum m in dp[T][m]
    int ans = 0;
    for(int m=0;m<=10000;m++) {
        if(dp[T][m] > ans) ans = dp[T][m];
    }
    cout << ans;
}