#include <iostream>
#include <vector>
#include <deque>
#include <algorithm>
using namespace std;

typedef long long ll;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n;
    ll d, k;
    cin >> n >> d >> k;
    vector<pair<ll, ll>> squares(n);
    for(int i=0;i<n;i++) cin >> squares[i].first >> squares[i].second;
    // Binary search on g
    ll left = 0, right = 1000000000, answer = -1;
    while(left <= right){
        ll mid = left + (right - left)/2;
        // Determine min_jump and max_jump
        ll min_jump, max_jump;
        if(mid < d){
            min_jump = d - mid;
            max_jump = d + mid;
        }
        else{
            min_jump = 1;
            max_jump = d + mid;
        }
        // DP
        vector<ll> dp(n, -1e18);
        // deque for sliding window maximum
        deque<int> dq;
        int window_start =0, window_end=0;
        ll current_max = -1e18;
        ll global_max = -1e18;
        for(int i=0;i<n;i++){
            ll xi = squares[i].first;
            // Update window_start
            ll min_pos = xi - max_jump;
            ll max_pos = xi - min_jump;
            while(window_start <n && squares[window_start].first < min_pos){
                if(!dq.empty() && dq.front() == window_start){
                    dq.pop_front();
                }
                window_start++;
            }
            // Update window_end
            while(window_end <n && squares[window_end].first <= max_pos){
                while(!dq.empty() && dp[window_end] >= dp[dq.back()]){
                    dq.pop_back();
                }
                dq.push_back(window_end);
                window_end++;
            }
            // Remove out of window
            while(!dq.empty() && dq.front() < window_start){
                dq.pop_front();
            }
            // Calculate dp[i]
            if(!dq.empty() && dp[dq.front()] != -1e18){
                dp[i] = squares[i].second + dp[dq.front()];
            }
            // Check if can jump from start
            if(xi >= min_jump && xi <= max_jump){
                dp[i] = max(dp[i], squares[i].second);
            }
            global_max = max(global_max, dp[i]);
            // Maintain deque for next iterations
        }
        if(global_max >=k){
            answer = mid;
            right = mid -1;
        }
        else{
            left = mid +1;
        }
    }
    cout << answer;
}