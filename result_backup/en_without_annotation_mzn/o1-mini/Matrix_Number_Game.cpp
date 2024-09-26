#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n, m;
    cin >> n >> m;
    vector<vector<int>> number(n, vector<int>(m));
    for(auto &row: number) for(auto &x: row) cin >> x;
    ll total_score = 0;
    for(int row_idx=0; row_idx<n; row_idx++){
        vector<ll> dp_prev(m+1, LLONG_MIN);
        dp_prev[0] = 0;
        for(int i=1;i<=m;i++){
            vector<ll> dp_curr(m+1, LLONG_MIN);
            for(int h=0; h<=i-1; h++){
                if(dp_prev[h]==LLONG_MIN) continue;
                // Choose head
                int h_new = h +1;
                if(h_new <= m){
                    ll score_head = dp_prev[h] + ((1ULL << i) * (ll)number[row_idx][h_new-1]);
                    dp_curr[h_new] = max(dp_curr[h_new], score_head);
                }
                // Choose tail
                // k = t +1 = (i - h) +1
                // index = m +1 - k = m -i + h
                int index = m - i + h;
                if(index >=0 && index < m){
                    ll score_tail = dp_prev[h] + ((1ULL << i) * (ll)number[row_idx][index]);
                    dp_curr[h] = max(dp_curr[h], score_tail);
                }
            }
            dp_prev = move(dp_curr);
        }
        ll max_score = LLONG_MIN;
        for(auto val: dp_prev) max_score = max(max_score, val);
        total_score += max_score;
    }
    cout << total_score;
}