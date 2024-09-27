#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

int main() {
    int n, m, S;
    cin >> n >> m >> S;
    
    vector<pair<int, int>> ores(n);
    for (int i = 0; i < n; ++i) {
        cin >> ores[i].first >> ores[i].second;
    }
    
    vector<pair<int, int>> intervals(m);
    for (int i = 0; i < m; ++i) {
        cin >> intervals[i].first >> intervals[i].second;
    }
    
    int min_diff = INT_MAX;
    int best_W = 0;
    
    for (int W = 0; W <= 1000; ++W) {
        int Y = 0;
        
        for (int i = 0; i < m; ++i) {
            int count = 0;
            int sum_quality = 0;
            
            for (int j = intervals[i].first - 1; j < intervals[i].second; ++j) {
                if (ores[j].first >= W) {
                    count++;
                    sum_quality += ores[j].second;
                }
            }
            
            Y += count * sum_quality;
        }
        
        int diff = abs(S - Y);
        if (diff < min_diff) {
            min_diff = diff;
            best_W = W;
        }
    }
    
    cout << min_diff << endl;
    
    return 0;
}
