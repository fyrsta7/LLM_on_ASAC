#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    int n;
    cin >> n;
    vector<int> ty(n), price(n), time(n);
    for (int i = 0; i < n; ++i) {
        cin >> ty[i] >> price[i] >> time[i];
    }

    vector<int> dp(n + 1, 1e9);
    dp[0] = 0;

    for (int i = 1; i <= n; ++i) {
        if (ty[i - 1] == 0) {
            dp[i] = dp[i - 1] + price[i - 1];
        } else {
            dp[i] = dp[i - 1];
            for (int j = i - 1; j >= 1; --j) {
                if (time[i - 1] - time[j - 1] <= 45 && price[j - 1] >= price[i - 1]) {
                    dp[i] = min(dp[i], dp[j - 1] + price[i - 1]);
                }
            }
        }
    }

    cout << dp[n] << endl;
    return 0;
}