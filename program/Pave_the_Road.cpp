#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    int n;
    cin >> n;
    vector<int> d(n);
    
    for (int i = 0; i < n; i++)
        cin >> d[i];

    int total_days = 0;

    while (true) {
        int i = 0;
        while (i < n && d[i] == 0)
            i++;
        if (i == n)
            break;

        int min_depth = INT_MAX;
        while (i < n && d[i] > 0) {
            min_depth = min(min_depth, d[i]);
            i++;
        }

        total_days += min_depth;
        for (int j = 0; j < n; j++) {
            if (d[j] > 0) d[j] -= min_depth;
        }
    }

    cout << total_days << endl;
    return 0;
}