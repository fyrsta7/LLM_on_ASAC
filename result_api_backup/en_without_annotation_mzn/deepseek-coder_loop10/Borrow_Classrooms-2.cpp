#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    int n, m;
    cin >> n >> m;
    vector<int> r(n + 1);
    for (int i = 1; i <= n; ++i) cin >> r[i];
    vector<int> d(m + 1), s(m + 1), t(m + 1);
    for (int i = 1; i <= m; ++i) cin >> d[i] >> s[i] >> t[i];

    vector<int> prefix_sum(n + 2, 0);
    for (int i = 1; i <= n; ++i) prefix_sum[i] = prefix_sum[i - 1] + r[i];

    auto check = [&](int k) {
        vector<int> delta(n + 2, 0);
        for (int i = 1; i <= k; ++i) {
            delta[s[i]] += d[i];
            delta[t[i] + 1] -= d[i];
        }
        for (int i = 1; i <= n; ++i) {
            delta[i] += delta[i - 1];
            if (delta[i] > prefix_sum[i]) return false;
        }
        return true;
    };

    int lo = 1, hi = m, ans = 0;
    while (lo <= hi) {
        int mid = (lo + hi) / 2;
        if (check(mid)) {
            ans = mid;
            lo = mid + 1;
        } else {
            hi = mid - 1;
        }
    }

    if (ans == m) cout << "0" << endl;
    else cout << "-1\n" << ans + 1 << endl;

    return 0;
}
