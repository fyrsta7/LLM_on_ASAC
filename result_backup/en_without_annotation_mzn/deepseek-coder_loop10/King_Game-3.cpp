#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>

using namespace std;

int main() {
    int n, a, b;
    cin >> n >> a >> b;
    vector<pair<int, int>> minister(n);
    for (int i = 0; i < n; ++i) {
        cin >> minister[i].first >> minister[i].second;
    }

    vector<int> order(n);
    for (int i = 0; i < n; ++i) {
        order[i] = i;
    }

    int minAnswer = INT_MAX;

    do {
        vector<int> money(n);
        money[0] = a / minister[order[0]].second;
        for (int i = 1; i < n; ++i) {
            int product = a;
            for (int j = 0; j < i; ++j) {
                product *= minister[order[j]].first;
            }
            money[i] = product / minister[order[i]].second;
        }

        int maxMoney = *max_element(money.begin(), money.end());
        minAnswer = min(minAnswer, maxMoney);

    } while (next_permutation(order.begin(), order.end()));

    cout << minAnswer << endl;

    return 0;
}