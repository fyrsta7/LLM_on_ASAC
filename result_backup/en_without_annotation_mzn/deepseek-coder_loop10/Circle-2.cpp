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
    int current = 1;

    for (int i = 1; i <= len; ++i) {
        current = (current * n) % len;
        suffix[i] = current;
        if (current == suffix[1]) {
            seen.insert(i);
        }
    }

    if (seen.empty()) {
        cout << "-1" << endl;
    } else {
        int min_out = *min_element(seen.begin(), seen.end()) - 1;
        cout << min_out << endl;
    }

    return 0;
}