#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <iomanip>
#include <climits>

using namespace std;

struct Point {
    double x, y;
};

vector<vector<int>> get_trajectories(const vector<Point>& pigs) {
    int n = pigs.size();
    vector<vector<int>> trajectories;
    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n; ++j) {
            double x1 = pigs[i].x, y1 = pigs[i].y;
            double x2 = pigs[j].x, y2 = pigs[j].y;
            if (x1 == x2) continue;
            double a = (y2 / x2 - y1 / x1) / (x2 - x1);
            if (a >= 0) continue;
            double b = y1 / x1 - a * x1;
            vector<int> trajectory;
            for (int k = 0; k < n; ++k) {
                double x = pigs[k].x, y = pigs[k].y;
                if (abs(a * x * x + b * x - y) < 1e-6) {
                    trajectory.push_back(k);
                }
            }
            if (!trajectory.empty()) {
                trajectories.push_back(trajectory);
            }
        }
    }
    for (int i = 0; i < n; ++i) {
        trajectories.push_back({i});
    }
    return trajectories;
}

int min_birds(const vector<Point>& pigs, int m) {
    int n = pigs.size();
    vector<vector<int>> trajectories = get_trajectories(pigs);
    int t = trajectories.size();
    vector<vector<int>> dp(1 << n, vector<int>(t, INT_MAX / 2));
    dp[0][0] = 0;
    for (int mask = 0; mask < (1 << n); ++mask) {
        for (int i = 0; i < t; ++i) {
            if (dp[mask][i] == INT_MAX / 2) continue;
            for (int j = 0; j < t; ++j) {
                int new_mask = mask;
                for (int k : trajectories[j]) {
                    new_mask |= (1 << k);
                }
                dp[new_mask][j] = min(dp[new_mask][j], dp[mask][i] + 1);
            }
        }
    }
    int ans = INT_MAX;
    for (int i = 0; i < t; ++i) {
        ans = min(ans, dp[(1 << n) - 1][i]);
    }
    if (m == 1) {
        ans = min(ans, (n + 2) / 3 + 1);
    } else if (m == 2) {
        for (const auto& traj : trajectories) {
            if (traj.size() >= n / 3) {
                ans = 1;
                break;
            }
        }
    }
    return ans;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T;
    cin >> T;
    while (T--) {
        int n, m;
        cin >> n >> m;
        vector<Point> pigs(n);
        for (int i = 0; i < n; ++i) {
            cin >> pigs[i].x >> pigs[i].y;
        }
        cout << min_birds(pigs, m) << '\n';
    }
    return 0;
}
