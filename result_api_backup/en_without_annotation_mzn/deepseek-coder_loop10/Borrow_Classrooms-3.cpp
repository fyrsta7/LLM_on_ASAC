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

    auto check = [&](int k) {
        vector<int> rooms = r;
        for (int i = 0; i < k; ++i) {
            rooms[s[i] - 1] -= d[i];
            if (t[i] < n) rooms[t[i]] += d[i];
        }
        for (int i = 1; i < n; ++i) rooms[i] += rooms[i - 1];
        for (int i = 0; i < n; ++i) if (rooms[i] < 0) return false;
        return true;
    };

    int lo = 0, hi = m + 1;
    while (lo < hi) {
        int mid = (lo + hi) / 2;
        if (check(mid)) lo = mid + 1;
        else hi = mid;
    }

    if (lo == m + 1) cout << "0" << endl;
    else cout << "-1\n" << lo << endl;

    return 0;
}
