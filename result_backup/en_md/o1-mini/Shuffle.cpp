#include <iostream>
#include <vector>
#include <algorithm>
#include <utility>
#include <cstdint>
using namespace std;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n, m;
    cin >> n >> m;
    vector<int> t(n);
    for(int &x:t) cin >> x;
    sort(t.begin(), t.end());
    // 1-based for prefix sum
    vector<long long> pre_sum(n+1, 0);
    for(int i=1;i<=n;i++) pre_sum[i] = pre_sum[i-1] + t[i-1];
    // dp_states[i] is a vector of pairs (departure_time, total_wait)
    vector<vector<pair<int, long long>>> dp_states(n+1);
    dp_states[0].emplace_back(0, 0LL);
    for(int i=1;i<=n;i++){
        vector<pair<int, long long>> temp;
        for(int j=0;j<i;j++){
            for(auto &[dep_j, dp_j] : dp_states[j]){
                int d = max(t[i-1], dep_j + m);
                long long total_wait = (long long)d * (i - j) - (pre_sum[i] - pre_sum[j]);
                long long new_dp = dp_j + total_wait;
                temp.emplace_back(d, new_dp);
            }
        }
        // Sort temp by departure time
        sort(temp.begin(), temp.end());
        // Prune to keep only the minimal dp for increasing d
        vector<pair<int, long long>> pruned;
        long long min_dp = 1e18;
        for(auto &[d, dp_val] : temp){
            if(dp_val < min_dp){
                pruned.emplace_back(d, dp_val);
                min_dp = dp_val;
            }
        }
        dp_states[i] = move(pruned);
    }
    long long answer = 1e18;
    for(auto &[d, dp_val] : dp_states[n]){
        if(dp_val < answer){
            answer = dp_val;
        }
    }
    cout << answer;
}