#include <iostream>
#include <vector>
#include <unordered_set>
#include <cmath>
#include <algorithm>

using namespace std;

int main() {
    int n, k;
    cin >> n >> k;
    int len = pow(10, k);
    vector<int> suffix(len + 1);
    unordered_set<int> seen;
    int first_suffix = -1;

    for (int i = 1; i <= len; ++i) {
        suffix[i] = (int)pow(n, i) % len;
        if (i == 1) {
            first_suffix = suffix[i];
        } else if (suffix[i] == first_suffix) {
            cout << i - 1 << endl;
            return 0;
        }
    }

    cout << -1 << endl;
    return 0;
}