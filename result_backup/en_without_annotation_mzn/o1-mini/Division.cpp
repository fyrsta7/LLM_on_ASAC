#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n;
    cin >> n;
    vector<int> a(n);
    for(auto &x: a) cin>>x;
    // Compute prefix sums
    vector<ll> prefix(n+1, 0);
    for(int i=0;i<n;i++) prefix[i+1] = prefix[i] + a[i];
    // Initialize DP
    // Use vector of unordered_map is too slow, use vector of vectors
    // Let max_sum be prefix[n]
    ll max_sum = prefix[n];
    // To save memory, use two vectors
    vector<ll> dp_prev(max_sum+1, LLONG_MAX);
    dp_prev[0] = 0;
    for(int i=0;i<n;i++){
        vector<ll> dp_curr(max_sum+1, LLONG_MAX);
        for(ll s_prev=0; s_prev <= prefix[i] && s_prev <= max_sum; s_prev++){
            if(dp_prev[s_prev] == LLONG_MAX) continue;
            for(int j=i+1; j<=n; j++){
                ll s_current = prefix[j] - prefix[i];
                if(s_current >= s_prev){
                    if(s_current > max_sum) continue;
                    dp_curr[s_current] = min(dp_curr[s_current], dp_prev[s_prev] + s_current * s_current);
                }
            }
        }
        dp_prev = move(dp_curr);
    }
    ll ans = LLONG_MAX;
    for(ll s=0; s<=max_sum; s++) {
        if(dp_prev[s] < ans) ans = dp_prev[s];
    }
    cout << ans;
}