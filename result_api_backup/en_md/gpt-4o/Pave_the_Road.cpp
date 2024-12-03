#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    int n;
    cin >> n;
    vector<int> d(n);
    for (int i = 0; i < n; ++i) {
        cin >> d[i];
    }

    int days = 0;
    for (int i = 0; i < n; ) {
        if (d[i] == 0) {
            i++;
            continue;
        }
        int min_depth = d[i];
        int j = i;
        while (j < n && d[j] > 0) {
            min_depth = min(min_depth, d[j]);
            j++;
        }
        for (int k = i; k < j; k++) {
            d[k] -= min_depth;
        }
        days += min_depth;
    }

    cout << days << endl;
    return 0;
}