#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
using namespace std;

typedef long long ll;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n, m, p;
    cin >> n >> m >> p;
    // 1-based indexing
    vector<vector<int>> coins(n +1, vector<int>(m +1, 0));
    for(int s=1;s<=n;s++) {
        for(int t=1;t<=m;t++) {
            cin >> coins[s][t];
        }
    }
    vector<int> cost(n +1, 0);
    for(int s=1;s<=n;s++) cin >> cost[s];
    // Initialize dp
    vector<ll> dp(m +1, LLONG_MIN);
    dp[0] = 0;
    // Initialize sum_prev
    vector<ll> sum_prev(n +1, 0);
    // Temporary sum_current
    vector<ll> sum_current(n +1, 0);
    for(int k=1;k<=p;k++) {
        for(int t=k;t<=m;t++) {
            ll max_sum = LLONG_MIN;
            for(int s=1;s<=n;s++) {
                if(k ==1){
                    sum_current[s] = (ll)coins[s][t] - (ll)cost[s];
                }
                else{
                    int s_shifted = (s + k -2) % n +1;
                    sum_current[s] = sum_prev[s_shifted] + (ll)coins[s_shifted][t];
                }
                if(sum_current[s] > max_sum){
                    max_sum = sum_current[s];
                }
            }
            if(dp[t -k] != LLONG_MIN){
                dp[t] = max(dp[t], dp[t -k] + max_sum);
            }
        }
        // Update sum_prev for next k
        for(int t=k;t<=m;t++) {
            for(int s=1;s<=n;s++) {
                if(k ==1){
                    sum_prev[s] = (ll)coins[s][t] - (ll)cost[s];
                }
                else{
                    int s_shifted = (s + k -2) % n +1;
                    sum_prev[s] += (ll)coins[s_shifted][t];
                }
            }
        }
    }
    ll result = LLONG_MIN;
    for(int t=1;t<=m;t++) {
        result = max(result, dp[t]);
    }
    cout << result;
}
