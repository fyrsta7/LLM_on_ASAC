#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

int main() {
    int n, k;
    cin >> n >> k;
    int len = pow(10, k);
    vector<int> suffix(len + 1);
    suffix[1] = n % len;
    for (int i = 2; i <= len; ++i) {
        suffix[i] = (suffix[i - 1] * n) % len;
    }
    int first_suffix = suffix[1];
    int period_start = -1;
    for (int i = 2; i <= len; ++i) {
        if (suffix[i] == first_suffix) {
            period_start = i;
            break;
        }
    }
    if (period_start == -1) {
        cout << "-1" << endl;
    } else {
        cout << period_start - 1 << endl;
    }
    return 0;
}