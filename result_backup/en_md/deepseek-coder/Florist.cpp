#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    int n;
    cin >> n;
    vector<int> heights(n);
    for (int i = 0; i < n; ++i) {
        cin >> heights[i];
    }

    if (n == 1) {
        cout << 1 << endl;
        return 0;
    }

    int maxLen = 1;
    int len = 1;
    for (int i = 1; i < n; ++i) {
        if (heights[i] != heights[i - 1]) {
            len++;
            maxLen = max(maxLen, len);
        } else {
            len = 1;
        }
    }

    cout << maxLen << endl;
    return 0;
}
