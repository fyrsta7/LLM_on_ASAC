#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Item {
    int weight, value, parent;
};

int main() {
    int N, m;
    cin >> N >> m;
    vector<Item> items(m);
    for (int i = 0; i < m; ++i) {
        cin >> items[i].weight >> items[i].value >> items[i].parent;
    }

    vector<int> dp(N + 1, 0);

    for (int i = 0; i < m; ++i) {
        if (items[i].parent == 0) {
            for (int j = N; j >= items[i].weight; --j) {
                dp[j] = max(dp[j], dp[j - items[i].weight] + items[i].weight * items[i].value);
            }
        }
    }

    cout << dp[N] << endl;

    return 0;
}