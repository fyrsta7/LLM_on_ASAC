#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Item {
    int price;
    int importance;
    int mainItemIndex;
};

int main() {
    int n, m;
    cin >> n >> m;
    n /= 10;

    vector<Item> items(m);
    vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0));

    for (int i = 0; i < m; ++i) {
        int v, p, q;
        cin >> v >> p >> q;
        items[i] = {v / 10, p, q};
    }

    for (int i = 1; i <= m; ++i) {
        int price = items[i-1].price;
        int importance = items[i-1].importance;
        int mainIndex = items[i-1].mainItemIndex - 1;

        if (mainIndex == -1) { // It's a main item
            for (int j = n; j >= price; --j) {
                dp[i][j] = max(dp[i][j], dp[i-1][j-price] + price * importance);
            }
        } else { // It's an accessory
            // If we don't buy the main item, we can't buy this accessory
            for (int j = 0; j <= n; ++j) {
                dp[i][j] = dp[i-1][j];
            }
            // If we buy the main item, we can consider buying this accessory
            for (int j = n; j >= price; --j) {
                if (j >= price + dp[mainIndex+1][j-price]) {
                    dp[i][j] = max(dp[i][j], dp[i-1][j-price] + price * importance);
                }
            }
        }
    }

    cout << dp[m][n] * 10 << endl;
    return 0;
}
