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
    for (int i = m; i < n; ++i) {
        right += num[i] * (i - m);
    }

    if (p1 < m) {
        left += s1 * (m - p1);
    } else if (p1 > m) {
        right += s1 * (p1 - m);
    }

    long long minDiff = abs(left - right);
    int bestP2 = 1;

    for (int p2 = 1; p2 <= n; ++p2) {
        long long newLeft = left;
        long long newRight = right;

        if (p2 < m) {
            newLeft += s2 * (m - p2);
        } else if (p2 > m) {
            newRight += s2 * (p2 - m);
        }

        long long diff = abs(newLeft - newRight);
        if (diff < minDiff) {
            minDiff = diff;
            bestP2 = p2;
        }
    }

    cout << "p2=" << bestP2 << endl;
    return 0;
}