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

    auto can_apply = [&](int k) -> bool {
        vector<int> delta(n + 2, 0);
        for (int i = 1; i <= k; ++i) {
            delta[s[i]] += d[i];
            delta[t[i] + 1] -= d[i];
        }
        vector<int> current_state(n + 1, 0);
        for (int i = 1; i <= n; ++i) {
            current_state[i] = current_state[i - 1] + delta[i];
            if (current_state[i] > prefix_sum[i]) return false;
        }
        return true;
    };

    int low = 1, high = m, ans = m + 1;
    while (low <= high) {
        int mid = (low + high) / 2;
        if (can_apply(mid)) {
            low = mid + 1;
        } else {
            ans = mid;
            high = mid - 1;
        }
    }

    if (ans == m + 1) cout << "0" << endl;
    else cout << "-1\n" << ans << endl;

    return 0;
}
