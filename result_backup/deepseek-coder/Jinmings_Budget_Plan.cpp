#include <iostream>
#include <vector>
using namespace std;

struct Item {
    int price, importance, mainItem;
};

int main() {
    int n, m;
    cin >> n >> m;
    vector<Item> items(m);
    for (int i = 0; i < m; ++i) {
        cin >> items[i].price >> items[i].importance >> items[i].mainItem;
    }

    vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0));
    vector<vector<int>> accessory(m + 1);

    for (int i = 0; i < m; ++i) {
        if (items[i].mainItem != 0) {
            accessory[items[i].mainItem].push_back(i + 1);
        }
    }

    for (int i = 1; i <= m; ++i) {
        if (items[i - 1].mainItem != 0) continue;
        for (int j = n; j >= items[i - 1].price; --j) {
            dp[i][j] = max(dp[i][j], dp[i - 1][j - items[i - 1].price] + items[i - 1].price * items[i - 1].importance);
            if (accessory[i].size() >= 1) {
                int acc1 = accessory[i][0];
                if (j >= items[i - 1].price + items[acc1 - 1].price) {
                    dp[i][j] = max(dp[i][j], dp[i - 1][j - items[i - 1].price - items[acc1 - 1].price] + items[i - 1].price * items[i - 1].importance + items[acc1 - 1].price * items[acc1 - 1].importance);
                }
            }
            if (accessory[i].size() == 2) {
                int acc2 = accessory[i][1];
                if (j >= items[i - 1].price + items[acc2 - 1].price) {
                    dp[i][j] = max(dp[i][j], dp[i - 1][j - items[i - 1].price - items[acc2 - 1].price] + items[i - 1].price * items[i - 1].importance + items[acc2 - 1].price * items[acc2 - 1].importance);
                }
                if (j >= items[i - 1].price + items[acc1 - 1].price + items[acc2 - 1].price) {
                    dp[i][j] = max(dp[i][j], dp[i - 1][j - items[i - 1].price - items[acc1 - 1].price - items[acc2 - 1].price] + items[i - 1].price * items[i - 1].importance + items[acc1 - 1].price * items[acc1 - 1].importance + items[acc2 - 1].price * items[acc2 - 1].importance);
                }
            }
        }
        for (int j = 0; j <= n; ++j) {
            dp[i][j] = max(dp[i][j], dp[i - 1][j]);
        }
    }

    cout << dp[m][n] << endl;
    return 0;
}
