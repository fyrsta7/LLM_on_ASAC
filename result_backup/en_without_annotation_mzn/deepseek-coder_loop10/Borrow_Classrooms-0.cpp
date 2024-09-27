#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    int n, m;
    cin >> n >> m;
    vector<int> r(n);
    for (int i = 0; i < n; ++i) cin >> r[i];
    vector<int> d(m), s(m), t(m);
    for (int i = 0; i < m; ++i) cin >> d[i] >> s[i] >> t[i];

    vector<int> prefix_sum(n + 1, 0);
    for (int i = 0; i < n; ++i) prefix_sum[i + 1] = prefix_sum[i] + r[i];

    auto can_perform = [&](int k) -> bool {
        vector<int> delta(n + 1, 0);
        for (int i = 0; i <= k; ++i) {
            delta[s[i] - 1] += d[i];
            delta[t[i]] -= d[i];
        }
        int current_delta = 0;
        for (int i = 0; i < n; ++i) {
            current_delta += delta[i];
            if (current_delta > prefix_sum[i + 1] - prefix_sum[0]) return false;
        }
        return true;
    };

    int left = 0, right = m;
    while (left < right) {
        int mid = (left + right + 1) / 2;
        if (can_perform(mid)) left = mid;
        else right = mid - 1;
    }

    if (left == m) cout << "0" << endl;
    else cout << "-1\n" << left + 1 << endl;

    return 0;
}
