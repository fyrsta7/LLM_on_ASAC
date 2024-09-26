#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <limits>

using namespace std;

struct Ore {
    int weight, value;
};

struct Interval {
    int left, right;
};

long long test_value(const vector<Ore>& ores, const vector<Interval>& intervals, long long W) {
    long long total_value = 0;
    for (const auto& interval : intervals) {
        long long interval_value = 0;
        for (int i = interval.left - 1; i < interval.right; ++i) {
            if (ores[i].weight <= W) {
                interval_value += ores[i].value;
            }
        }
        total_value += interval_value;
    }
    return total_value;
}

int main() {
    int n, m;
    long long s;
    cin >> n >> m >> s;
    
    vector<Ore> ores(n);
    for (int i = 0; i < n; ++i) {
        cin >> ores[i].weight >> ores[i].value;
    }
    
    vector<Interval> intervals(m);
    for (int i = 0; i < m; ++i) {
        cin >> intervals[i].left >> intervals[i].right;
    }
    
    long long left = 0, right = 1000000, min_diff = numeric_limits<long long>::max(), best_W = 0;
    
    while (left <= right) {
        long long mid = left + (right - left) / 2;
        long long current_value = test_value(ores, intervals, mid);
        long long diff = abs(s - current_value);
        
        if (diff < min_diff) {
            min_diff = diff;
            best_W = mid;
        }
        
        if (current_value < s) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    
    cout << min_diff << endl;
    
    return 0;
}
