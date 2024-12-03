#include <iostream>
#include <vector>
#include <algorithm>
#include <limits>

using namespace std;

int main() {
    int n, d, k;
    cin >> n >> d >> k;
    vector<int> X(n), S(n);
    for (int i = 0; i < n; ++i) cin >> X[i];
    for (int i = 0; i < n; ++i) cin >> S[i];

    int lo = 0, hi = 2 * d, ans = hi;
    while (lo <= hi) {
        int mid = (lo + hi) / 2;
        bool possible = false;
        int sum = 0;
        for (int i = 0; i < n; ++i) {
            if (X[i] >= d - mid && X[i] <= d + mid) {
                sum += S[i];
                if (sum >= k) {
                    possible = true;
                    break;
                }
                int j = i + 1;
                while (j < n && X[j] - X[i] <= d + mid && X[j] - X[i] >= d - mid) {
                    sum += S[j];
                    if (sum >= k) {
                        possible = true;
                        break;
                    }
                    ++j;
                }
                if (possible) break;
                sum = 0;
            }
        }
        if (possible) {
            ans = mid;
            hi = mid - 1;
        } else {
            lo = mid + 1;
        }
    }
    cout << ans << endl;
    return 0;
}