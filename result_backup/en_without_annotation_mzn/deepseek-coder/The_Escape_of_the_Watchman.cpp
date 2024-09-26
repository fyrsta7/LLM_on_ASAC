#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    int M, S, T;
    cin >> M >> S >> T;

    vector<int> dp(T + 1, 0);
    vector<int> mana(T + 1, 0);
    mana[0] = M;

    for (int i = 1; i <= T; ++i) {
        if (mana[i - 1] >= 10) {
            dp[i] = dp[i - 1] + 60;
            mana[i] = mana[i - 1] - 10;
        } else {
            dp[i] = dp[i - 1] + 17;
            mana[i] = mana[i - 1];
        }

        if (dp[i] >= S) {
            cout << "Yes\n" << i << endl;
            return 0;
        }

        if (i + 1 <= T) {
            dp[i + 1] = max(dp[i + 1], dp[i]);
            mana[i + 1] = max(mana[i + 1], mana[i] + 4);
        }
    }

    cout << "No\n" << dp[T] << endl;
    return 0;
}
