#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    int n, m;
    cin >> n >> m;
    vector<int> w(n+1); // 1-based indexing
    for (int i = 1; i <= n; ++i)
        cin >> w[i];
        
    vector<int> start(n + 1, 0);
    
    // Initialize start times for the first m tasks:
    for(int i = 1; i <= m; ++i) {
        start[i] = 0;
    }

    for(int i = m + 1; i <= n; ++i) {
        vector<int> latest(m + 1, 0);
        for (int j = 1; j <= m; ++j) {
            for (int k = 1; k < i; ++k) {
                if(j == (k % m == 0 ? m : k % m)) {
                    latest[j] = max(latest[j], k);
                }
            }
        }
        int min_start = start[latest[1]] + w[latest[1]];
        for (int j = 2; j <= m; ++j) {
            min_start = min(min_start, start[latest[j]] + w[latest[j]]);
        }
        start[i] = min_start;
        
        for (int j = 1; j <= m; ++j) {
            if(start[latest[(i % m == 0 ? m : i % m)]] + w[latest[(i % m == 0 ? m : i % m)]] <= start[latest[j]] + w[latest[j]]) {
                start[i] = max(start[i], start[latest[j]] + w[latest[j]]);
            }
        }
    }

    int final_max = 0;
    for(int i = 1; i <= n; ++i) {
        final_max = max(final_max, start[i] + w[i]);
    }

    cout << final_max << endl;
    return 0;
}