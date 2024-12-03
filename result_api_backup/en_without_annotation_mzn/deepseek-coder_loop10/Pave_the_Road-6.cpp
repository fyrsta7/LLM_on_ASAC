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

    int actions = 0;
    while (true) {
        int max_val = *max_element(d.begin(), d.end());
        if (max_val == 0) break;

        int left = -1, right = -1;
        for (int i = 0; i < n; ++i) {
            if (d[i] == max_val) {
                if (left == -1) left = i;
                right = i;
            }
        }

        for (int i = left; i <= right; ++i) {
            d[i]--;
        }

        actions++;
    }

    cout << actions << endl;
    return 0;
}