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

    auto can_remove = [&](int k) -> bool {
        vector<int> delta(n + 1, 0);
        for (int i = 0; i <= k; ++i) {
            delta[s[i] - 1] += d[i];
            delta[t[i]] -= d[i];
        }
        for (int i = 1; i <= n; ++i) delta[i] += delta[i - 1];
        for (int i = 0; i < n; ++i) {
            if (delta[i] > prefix_sum[i + 1]) return false;
        }
        return true;
    };

    int lo = 0, hi = m;
    while (lo < hi) {
        int mid = (lo + hi + 1) / 2;
        if (can_remove(mid - 1)) lo = mid;
        else hi = mid - 1;
    }

    if (lo == m) cout << "0" << endl;
    else cout << "-1\n" << lo + 1 << endl;

    return 0;
}