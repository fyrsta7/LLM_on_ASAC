#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
using namespace std;

int main() {
    int L;
    cin >> L;
    
    int S, T, M;
    cin >> S >> T >> M;
    
    vector<int> pebbles_positions(M);
    for (int i = 0; i < M; ++i) {
        cin >> pebbles_positions[i];
    }
    
    // Sort the pebbles positions
    sort(pebbles_positions.begin(), pebbles_positions.end());

    // Compress positions to handle large L values by using differences
    int max_diff = pebbles_positions.back() - pebbles_positions[0] + 1;
    vector<int> positions(max_diff + 1, INT_MAX);
    for (int i = 0; i < M; ++i) {
        pebbles_positions[i] -= pebbles_positions[0] - 1;
    }

    // DP array for storing the minimum pebbles stepped on for each position
    vector<int> dp(max_diff + T + 1, INT_MAX);
    dp[0] = 0;  // Starting point

    for (int i = 0; i <= max_diff; ++i) {
        if (dp[i] == INT_MAX) continue;
        
        for (int j = S; j <= T; ++j) {
            int next_pos = i + j;
            if (next_pos > max_diff) break;
            int is_pebble = find(pebbles_positions.begin(), pebbles_positions.end(), next_pos) != pebbles_positions.end();
            dp[next_pos] = min(dp[next_pos], dp[i] + is_pebble);
        }
    }
    
    int result = INT_MAX;
    for (int i = L - (pebbles_positions[0] - 1); i <= max_diff; ++i) {
        result = min(result, dp[i]);
    }

    cout << result << endl;

    return 0;
}
