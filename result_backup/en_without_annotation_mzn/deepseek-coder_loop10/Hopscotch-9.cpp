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

    int left = 0, right = 1e9;
    while (left < right) {
        int mid = (left + right) / 2;
        bool possible = false;
        vector<int> dp(n, numeric_limits<int>::min());
        for (int i = 0; i < n; ++i) {
            if (X[i] >= d - mid && X[i] <= d + mid) {
                dp[i] = S[i];
                for (int j = 0; j < i; ++j) {
                    if (X[i] - X[j] >= d - mid && X[i] - X[j] <= d + mid) {
                        dp[i] = max(dp[i], dp[j] + S[i]);
                    }
                }
                if (dp[i] >= k) {
                    possible = true;
                    break;
                }
            }
        }
        if (possible) {
            right = mid;
        } else {
            left = mid + 1;
        }
    }

    cout << left << endl;
    return 0;
}
