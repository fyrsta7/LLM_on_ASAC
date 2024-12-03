#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

int main() {
    int n;
    cin >> n;
    vector<int> num(n);
    for (int i = 0; i < n; ++i) {
        cin >> num[i];
    }
    int m, p1, s1, s2;
    cin >> m >> p1 >> s1 >> s2;

    long long left_sum = 0, right_sum = 0;
    for (int i = 0; i < m - 1; ++i) {
        left_sum += num[i] * (m - i - 1);
    }
    for (int i = m; i < n; ++i) {
        right_sum += num[i] * (i - m);
    }

    if (p1 < m) {
        left_sum += s1 * (m - p1);
    } else if (p1 > m) {
        right_sum += s1 * (p1 - m);
    }

    long long min_diff = abs(left_sum - right_sum);
    int best_p2 = 1;

    for (int p2 = 1; p2 <= n; ++p2) {
        long long new_left_sum = left_sum;
        long long new_right_sum = right_sum;

        if (p2 < m) {
            new_left_sum += s2 * (m - p2);
        } else if (p2 > m) {
            new_right_sum += s2 * (p2 - m);
        }

        long long diff = abs(new_left_sum - new_right_sum);
        if (diff < min_diff) {
            min_diff = diff;
            best_p2 = p2;
        }
    }

    cout << "p2=" << best_p2 << endl;
    return 0;
}