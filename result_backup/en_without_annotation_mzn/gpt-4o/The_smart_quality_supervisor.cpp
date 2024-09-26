#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
using namespace std;

int main() {
    int n, m, S;
    cin >> n >> m >> S;
    vector<pair<int, int>> ores(n);
    vector<pair<int, int>> intervals(m);

    for (int i = 0; i < n; ++i)
        cin >> ores[i].first >> ores[i].second;

    for (int i = 0; i < m; ++i)
        cin >> intervals[i].first >> intervals[i].second;

    int best_abs_diff = INT_MAX, best_Y = 0, best_W = 0;

    for (int W = -10000; W <= 10000; ++W) {  // We assume W is within [-10^4, 10^4]
        int Y = 0;
        for (const auto& interval : intervals) {
            int interval_sum = 0, count = 0;
            for (int j = interval.first - 1; j < interval.second; ++j) {
                if (ores[j].first >= W) {
                    count++;
                    interval_sum += ores[j].second;
                }
            }
            Y += count * interval_sum;
        }
        int abs_diff = abs(S - Y);
        if (abs_diff < best_abs_diff) {
            best_abs_diff = abs_diff;
            best_Y = Y;
            best_W = W;
        }
        if (abs_diff == 0)
            break;  // Optimal solution found
    }

    cout << best_abs_diff << endl;
    return 0;
}