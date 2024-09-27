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

    int left = 0, right = 2 * 1000000000;
    while (left < right) {
        int mid = (left + right) / 2;
        bool valid = false;
        int sum = 0;
        for (int i = 0; i < n; ++i) {
            if (X[i] >= d - mid && X[i] <= d + mid) {
                sum += S[i];
                if (sum >= k) {
                    valid = true;
                    break;
                }
            } else {
                sum = 0;
            }
        }
        if (valid) {
            right = mid;
        } else {
            left = mid + 1;
        }
    }

    cout << left << endl;
    return 0;
}