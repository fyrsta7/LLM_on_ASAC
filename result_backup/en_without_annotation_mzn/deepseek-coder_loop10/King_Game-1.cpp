#include <iostream>
#include <vector>
#include <algorithm>
#include <limits>

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

    int min_answer = numeric_limits<int>::max();

    do {
        vector<int> money(n, 1);
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < i; ++j) {
                money[i] *= minister[order[j]].first;
            }
            money[i] /= minister[order[i]].second;
        }

        int max_money = *max_element(money.begin(), money.end());
        min_answer = min(min_answer, max_money);

    } while (next_permutation(order.begin(), order.end()));

    cout << min_answer << endl;
    return 0;
}