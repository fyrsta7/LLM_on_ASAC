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

    vector<int> state(n, 0);
    int actions = 0;

    while (true) {
        int left = -1, right = -1;
        for (int i = 0; i < n; ++i) {
            if (state[i] < h[i]) {
                if (left == -1) left = i;
                right = i;
            }
        }
        if (left == -1) break;

        for (int i = left; i <= right; ++i) {
            state[i]++;
        }
        actions++;
    }

    cout << actions << endl;
    return 0;
}