#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

typedef long long ll;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    ll s;
    cin >> n >> m >> s;

    vector<pair<int, int>> ores(n);
    for (int i = 0; i < n; ++i) {
        cin >> ores[i].first >> ores[i].second;
    }

    vector<pair<int, int>> intervals(m);
    for (int i = 0; i < m; ++i) {
        cin >> intervals[i].first >> intervals[i].second;
    }

    auto calculate_y = [&](int W) -> ll {
        ll total_y = 0;
        for (const auto& interval : intervals) {
            ll y_i = 0;
            for (int j = interval.first - 1; j < interval.second; ++j) {
                if (ores[j].first >= W) {
                    y_i += ores[j].second;
                }
            }
            total_y += y_i;
        }
        return total_y;
    };

    int left = 0, right = 1e6 + 1;
    ll min_diff = LLONG_MAX;

    while (left < right) {
        int mid = (left + right) / 2;
        ll y = calculate_y(mid);
        ll diff = abs(s - y);

        if (diff < min_diff) {
            min_diff = diff;
        }

        if (y < s) {
            right = mid;
        } else {
            left = mid + 1;
        }
    }

    cout << min_diff << endl;

    return 0;
}
