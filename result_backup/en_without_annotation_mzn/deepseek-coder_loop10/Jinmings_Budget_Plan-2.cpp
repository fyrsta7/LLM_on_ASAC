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
        for (int j = N; j >= items[i].weight; --j) {
            if (items[i].dependency == 0 || dp[j - items[i].weight] != 0) {
                dp[j] = max(dp[j], dp[j - items[i].weight] + items[i].weight * items[i].value);
            }
        }
    }

    cout << *max_element(dp.begin(), dp.end()) << endl;

    return 0;
}