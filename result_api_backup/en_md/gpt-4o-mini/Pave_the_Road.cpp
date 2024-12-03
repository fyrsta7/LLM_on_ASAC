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

    int total_days = 0;
    while (true) {
        int min_depth = *min_element(d.begin(), d.end());
        if (min_depth == 0) break;

        total_days += min_depth;
        for (int i = 0; i < n; ++i) {
            d[i] -= min_depth;
        }
    }

    cout << total_days << endl;
    return 0;
}