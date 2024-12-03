#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

int main() {
    int n, m, p1, s1, s2;
    cin >> n;
    vector<int> num(n);
    for (int i = 0; i < n; ++i) {
        cin >> num[i];
    }
    cin >> m >> p1 >> s1 >> s2;

    long long left = 0, right = 0;
    for (int i = 0; i < m - 1; ++i) {
        left += num[i] * (m - i - 1);
    }
    if (p1 < m) {
        left += s1 * (m - p1);
    }

    for (int i = m; i < n; ++i) {
        right += num[i] * (i - m + 1);
    }
    if (p1 > m) {
        right += s1 * (p1 - m);
    }

    long long min_diff = abs(left - right);
    int best_p2 = 1;

    for (int p2 = 1; p2 <= n; ++p2) {
        long long new_left = left;
        long long new_right = right;

        if (p2 < m) {
            new_left += s2 * (m - p2);
        } else if (p2 > m) {
            new_right += s2 * (p2 - m);
        }

        long long diff = abs(new_left - new_right);
        if (diff < min_diff) {
            min_diff = diff;
            best_p2 = p2;
        }
    }

    cout << "p2=" << best_p2 << endl;
    return 0;
}
