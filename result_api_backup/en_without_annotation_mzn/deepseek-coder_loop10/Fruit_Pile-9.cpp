#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    int n;
    cin >> n;
    vector<int> fruit(n);
    for (int i = 0; i < n; ++i) {
        cin >> fruit[i];
    }

    vector<int> stat(fruit);
    int stamina = 0;

    for (int i = 2; i <= n; ++i) {
        auto it1 = max_element(stat.begin(), stat.end());
        int idx1 = it1 - stat.begin();
        *it1 = 0;
        auto it2 = max_element(stat.begin(), stat.end());
        int idx2 = it2 - stat.begin();
        *it2 = 0;

        stat[idx1] += stat[idx2];
        stamina += stat[idx1];
    }

    cout << stamina << endl;
    return 0;
}
