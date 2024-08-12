#include <iostream>
#include <vector>
#include <algorithm>
#include <limits>

using namespace std;

struct Pipe {
    int position, lower, upper;
};

int main() {
    int n, m, k;
    cin >> n >> m >> k;

    vector<pair<int, int>> heights(n);
    for (int i = 0; i < n; i++) {
        cin >> heights[i].first >> heights[i].second;
    }

    vector<Pipe> pipes(k);
    for (int i = 0; i < k; i++) {
        cin >> pipes[i].position >> pipes[i].lower >> pipes[i].upper;
    }
    
    sort(pipes.begin(), pipes.end(), [](const Pipe &a, const Pipe &b) {
        return a.position < b.position;
    });

    // Dynamic Programming approach to track the bird's possible heights
    vector<int> dp(m + 1, numeric_limits<int>::max());
    dp[0] = 0;  // Initial height is 0 with 0 taps.

    for (int pos = 0; pos < n; ++pos) {
        vector<int> new_dp(m + 1, numeric_limits<int>::max());
        for (int h = 0; h <= m; ++h) {
            if (dp[h] != numeric_limits<int>::max()) {
                // Tap the screen
                int new_height = min(m, h + heights[pos].first);
                new_dp[new_height] = min(new_dp[new_height], dp[h] + 1);
                
                // Do not tap the screen
                new_height = max(0, h - heights[pos].second);
                new_dp[new_height] = min(new_dp[new_height], dp[h]);
            }
        }
        dp = new_dp;
    }

    int max_passed_gaps = 0;
    bool can_complete = false;
    int min_taps = numeric_limits<int>::max();

    for (int h = 0; h <= m; ++h) {
        // Check if the bird can complete the game
        if (dp[h] != numeric_limits<int>::max()) {
            can_complete = true;
            min_taps = min(min_taps, dp[h]);
        }
        
        // Count how many pipe gaps can be passed
        for (const Pipe &pipe : pipes) {
            if (pipe.position == n) break;  // Only consider pipes before the last position
            if (h >= pipe.lower && h <= pipe.upper) {
                max_passed_gaps++;
                break; // Pass this pipe gap
            }
        }
    }

    cout << (can_complete ? 1 : 0) << endl;
    cout << (can_complete ? min_taps : max_passed_gaps) << endl;

    return 0;
}