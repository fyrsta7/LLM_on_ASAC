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

    sort(minister.begin(), minister.end(), [](const pair<int, int>& x, const pair<int, int>& y) {
        return x.second * y.first < y.second * x.first;
    });

    int maxMoney = 0;
    int product = a;
    for (int i = 0; i < n; ++i) {
        int money = product / minister[i].second;
        maxMoney = max(maxMoney, money);
        product *= minister[i].first;
    }

    cout << maxMoney << endl;
    return 0;
}
