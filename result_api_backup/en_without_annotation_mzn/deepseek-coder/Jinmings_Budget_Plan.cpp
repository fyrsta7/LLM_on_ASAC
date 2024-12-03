#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Item {
    int weight, value, dependency;
};

int main() {
    int N, m;
    cin >> N >> m;
    vector<Item> items(m);
    for (int i = 0; i < m; ++i) {
        cin >> items[i].weight >> items[i].value >> items[i].dependency;
    }

    vector<int> dp(N + 1, 0);
    vector<bool> taken(m, false);

    for (int i = 0; i < m; ++i) {
        for (int j = N; j >= items[i].weight; --j) {
            if (items[i].dependency == 0 || taken[items[i].dependency - 1]) {
                dp[j] = max(dp[j], dp[j - items[i].weight] + items[i].value);
            }
        }
        if (items[i].dependency != 0) {
            taken[i] = true;
        }
    }

    cout << dp[N] << endl;
    return 0;
}
