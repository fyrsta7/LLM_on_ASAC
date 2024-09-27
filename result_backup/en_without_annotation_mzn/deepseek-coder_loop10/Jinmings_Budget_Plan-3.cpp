#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Item {
    int weight, value, dependency;
};

int N, m;
vector<Item> items;
vector<int> dp;

int main() {
    cin >> N >> m;
    items.resize(m);
    dp.resize(N + 1, 0);

    for (int i = 0; i < m; ++i) {
        cin >> items[i].weight >> items[i].value >> items[i].dependency;
    }

    for (int i = 0; i < m; ++i) {
        if (items[i].dependency != 0) continue;
        for (int j = N; j >= items[i].weight; --j) {
            dp[j] = max(dp[j], dp[j - items[i].weight] + items[i].value);
        }
    }

    for (int i = 0; i < m; ++i) {
        if (items[i].dependency == 0) continue;
        for (int j = N; j >= items[i].weight; --j) {
            if (dp[j - items[i].weight] >= dp[j]) continue;
            dp[j] = max(dp[j], dp[j - items[i].weight] + items[i].value);
        }
    }

    cout << dp[N] << endl;
    return 0;
}