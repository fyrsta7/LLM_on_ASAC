#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    int w, n;
    cin >> w >> n;
    vector<int> prices(n);
    for (int i = 0; i < n; ++i) {
        cin >> prices[i];
    }
    sort(prices.begin(), prices.end());

    int groups = 0;
    int left = 0, right = n - 1;
    while (left <= right) {
        if (prices[left] + prices[right] <= w) {
            left++;
        }
        right--;
        groups++;
    }
    cout << groups << endl;
    return 0;
}
