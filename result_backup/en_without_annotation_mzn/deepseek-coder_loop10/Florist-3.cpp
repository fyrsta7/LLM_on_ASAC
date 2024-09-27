#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    int n;
    cin >> n;
    vector<int> h(n);
    for (int i = 0; i < n; ++i) {
        cin >> h[i];
    }

    vector<int> dp_inc(n, 1), dp_dec(n, 1);

    for (int i = 1; i < n; ++i) {
        if (h[i] > h[i-1]) {
            dp_inc[i] = dp_dec[i-1] + 1;
        }
        if (h[i] < h[i-1]) {
            dp_dec[i] = dp_inc[i-1] + 1;
        }
    }

    int max_m = 0;
    for (int i = 0; i < n; ++i) {
        max_m = max(max_m, max(dp_inc[i], dp_dec[i]));
    }

    cout << max_m << endl;
    return 0;
}
