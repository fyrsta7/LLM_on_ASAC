#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    int n;
    cin >> n;
    vector<int> h(n);
    for (int i = 0; i < n; ++i) {
        cin >> h[i];
    }

    int max_h = *max_element(h.begin(), h.end());
    vector<int> dp(max_h + 1, n + 1);
    dp[0] = 0;

    for (int i = 1; i <= max_h; ++i) {
        for (int j = 0; j < n; ++j) {
            if (h[j] >= i) {
                int left = j;
                while (left > 0 && h[left - 1] >= i) --left;
                int right = j;
                while (right < n - 1 && h[right + 1] >= i) ++right;
                dp[i] = min(dp[i], dp[i - 1] + (right - left + 1));
            }
        }
    }

    cout << dp[max_h] << endl;
    return 0;
}
