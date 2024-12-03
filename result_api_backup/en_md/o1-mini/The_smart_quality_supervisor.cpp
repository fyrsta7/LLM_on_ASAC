#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <map>
#include <climits>
using namespace std;

typedef long long ll;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    ll n, m;
    ll S;
    cin >> n >> m >> S;
    vector<pair<ll, ll>> ores(n);
    for(int i=0;i<n;i++) cin >> ores[i].first >> ores[i].second;
    vector<pair<ll, ll>> intervals(m);
    ll l, r;
    // Initialize difference array
    vector<ll> diff(n+2, 0);
    for(int i=0;i<m;i++){
        cin >> l >> r;
        diff[l] +=1;
        diff[r+1] -=1;
    }
    // Compute c_j
    vector<ll> c(n+1, 0);
    for(int i=1;i<=n;i++){
        c[i] = c[i-1] + diff[i];
    }
    // Create a list of (w_j, c_j * v_j)
    vector<pair<ll, ll>> sorted_ores;
    for(int i=1;i<=n;i++){
        sorted_ores.emplace_back(ores[i-1].first, c[i] * ores[i-1].second);
    }
    // Sort by w_j
    sort(sorted_ores.begin(), sorted_ores.end(), [&](const pair<ll, ll> &a, const pair<ll, ll> &b) -> bool{
        if(a.first != b.first) return a.first < b.first;
        return false;
    });
    // Create prefix sums
    vector<ll> prefix_sum(n+1, 0);
    for(int i=1;i<=n;i++) prefix_sum[i] = prefix_sum[i-1] + sorted_ores[i-1].second;
    // Collect unique w_j
    vector<ll> unique_w;
    unique_w.push_back(sorted_ores[0].first);
    for(int i=1;i<n;i++) if(sorted_ores[i].first != sorted_ores[i-1].first) unique_w.push_back(sorted_ores[i].first);
    // Iterate over unique_w and find the minimum |S - Y|
    ll min_diff = LLONG_MAX;
    ll answer = 0;
    int ptr =0;
    for(auto W: unique_w){
        // Find the upper_bound
        ll Y =0;
        // Binary search to find the last index where w_j <= W
        int pos = upper_bound(sorted_ores.begin(), sorted_ores.end(), make_pair(W, LLONG_MAX)) - sorted_ores.begin();
        Y = prefix_sum[pos];
        ll diff_val = abs(S - Y);
        if(diff_val < min_diff){
            min_diff = diff_val;
            answer = diff_val;
        }
        // If multiple same diffs, take the smallest W, but not required as only minimum value is needed
    }
    // Also consider W less than all w_j
    // Y=0
    ll diff_zero = abs(S - 0LL);
    if(diff_zero < min_diff){
        min_diff = diff_zero;
    }
    cout << min_diff;
}