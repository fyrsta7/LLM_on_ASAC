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

    int left = 0, right = *max_element(X.begin(), X.end()) - *min_element(X.begin(), X.end());
    int result = right;

    while (left <= right) {
        int mid = (left + right) / 2;
        bool valid = false;

        for (int start = 0; start < n; ++start) {
            if (X[start] < d - mid || X[start] > d + mid) continue;
            int sum = S[start];
            for (int end = start + 1; end < n; ++end) {
                if (X[end] - X[start] < d - mid || X[end] - X[start] > d + mid) continue;
                sum += S[end];
                if (sum >= k) {
                    valid = true;
                    break;
                }
            }
            if (valid) break;
        }

        if (valid) {
            result = mid;
            right = mid - 1;
        } else {
            left = mid + 1;
        }
    }

    cout << result << endl;
    return 0;
}