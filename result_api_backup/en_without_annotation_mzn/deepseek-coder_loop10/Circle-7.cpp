#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    int n, k;
    cin >> n >> k;

    int len = 1;
    for (int i = 0; i < k; ++i) {
        len *= 10;
    }

    vector<int> suffix(len + 1);
    suffix[1] = n % len;

    for (int i = 2; i <= len; ++i) {
        suffix[i] = (suffix[i - 1] * n) % len;
    }

    int first_suffix = suffix[1];
    int min_cycle_length = -1;

    for (int i = 2; i <= len; ++i) {
        if (suffix[i] == first_suffix) {
            min_cycle_length = i - 1;
            break;
        }
    }

    cout << (min_cycle_length != -1 ? min_cycle_length : -1) << endl;

    return 0;
}