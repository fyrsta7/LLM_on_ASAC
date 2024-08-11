#include <iostream>
#include <vector>
#include <queue>
#include <limits.h>

using namespace std;

struct Square {
    long long x, s;
};

int main() {
    int n, d;
    long long k;
    cin >> n >> d >> k;
    vector<Square> squares(n);
    
    for(int i = 0; i < n; ++i) {
        cin >> squares[i].x >> squares[i].s;
    }
    
    vector<long long> dp(n, LONG_LONG_MIN);
    dp[0] = squares[0].s;
    deque<pair<int, int>> dq;
    dq.push_back({0, 0});
    
    for(int g = 0; g < n; ++g) {
        while(!dq.empty() && dq.front().second < g - (d + g)) {
            dq.pop_front();
        }
        if(!dq.empty()) {
            int idx = dq.front().first;
            if(squares[g].x - squares[idx].x <= d) {
                dp[g] = max(dp[g], dp[idx] + squares[g].s);
            }
        }
        while(!dq.empty() && dp[dq.back().first] <= dp[g]) {
            dq.pop_back();
        }
        dq.push_back({g, g + d});
    }
    
    long long max_points = LONG_LONG_MIN;
    for(int i = 0; i < n; ++i) {
        max_points = max(max_points, dp[i]);
    }
    
    if(max_points >= k) {
        cout << 0 << endl;
        return 0;
    }
    
    for(int g = 1; g <= 2000; ++g) {
        dq.clear();
        fill(dp.begin(), dp.end(), LONG_LONG_MIN);
        dp[0] = squares[0].s;
        dq.push_back({0, 0});
        
        for(int i = 1; i < n; ++i) {
            while(!dq.empty() && dq.front().second < i - (d + g)) {
                dq.pop_front();
            }
            if(!dq.empty()) {
                int idx = dq.front().first;
                int min_jump = max(1, d - g);
                for(int jump = min_jump; jump <= d + g; ++jump) {
                    if(i - jump >= 0 && squares[i].x - squares[i - jump].x == jump) {
                        dp[i] = max(dp[i], dp[i - jump] + squares[i].s);
                        break;
                    }
                }
            }
            while(!dq.empty() && dp[dq.back().first] <= dp[i]) {
                dq.pop_back();
            }
            dq.push_back({i, i + d});
        }
        
        for(int i = 0; i < n; ++i) {
            max_points = max(max_points, dp[i]);
        }
        
        if(max_points >= k) {
            cout << g << endl;
            return 0;
        }
    }
    
    cout << -1 << endl;
    return 0;
}
