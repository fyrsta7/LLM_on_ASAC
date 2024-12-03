#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const int INF = 1e9;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    int L, S, T, M;
    cin >> L >> S >> T >> M;
    vector<int> stones(M);
    for(auto &x: stones) cin >> x;
    int max_pos = L + T;
    vector<bool> is_stone(max_pos + 1, false);
    for(auto x: stones){
        if(x <= max_pos) is_stone[x] = true;
    }
    vector<int> dp(max_pos + 1, INF);
    dp[0] = 0;
    deque<int> dq;
    dq.push_back(0);
    for(int pos = 1; pos <= max_pos; pos++){
        // Remove positions out of window [pos-T, pos-S]
        while(!dq.empty() && dq.front() < pos - T) dq.pop_front();
        // Ensure the front is within [pos-T, pos-S]
        while(!dq.empty() && dq.front() < pos - S) break;
        // Now dq.front() should be >= pos-T and <= pos-S
        if(!dq.empty() && pos - S >=0){
            dp[pos] = dp[dq.front()] + (is_stone[pos] ? 1 : 0);
        }
        // Maintain deque: remove from back if current dp[pos] is smaller
        while(!dq.empty() && dp[pos] <= dp[dq.back()]) dq.pop_back();
        if(pos - S >=0 && pos <= max_pos){
            dq.push_back(pos);
        }
    }
    int ans = INF;
    for(int pos = L; pos <= max_pos; pos++) ans = min(ans, dp[pos]);
    cout << (ans < INF ? ans : -1);
}