#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

int main() {
    int n;
    cin >> n;
    vector<int> a(n), b(n);
    for (int i = 0; i < n; ++i) cin >> a[i];
    for (int i = 0; i < n; ++i) cin >> b[i];

    int max_exchange = n * n;
    int min_distance = max_exchange;

    sort(a.begin(), a.end());
    sort(b.begin(), b.end());

    int distance = 0;
    for (int i = 0; i < n; ++i) {
        distance += pow(a[i] - b[i], 2);
    }

    min_distance = min(min_distance, distance);

    int times1 = 0, times2 = 0;
    vector<int> state1 = a, state2 = b;

    while (times1 + times2 < max_exchange) {
        if (state1 == state2) break;

        if (times1 <= times2) {
            for (int i = 0; i < n - 1; ++i) {
                swap(state1[i], state1[i + 1]);
                ++times1;
                if (state1 == state2) break;
            }
        } else {
            for (int i = 0; i < n - 1; ++i) {
                swap(state2[i], state2[i + 1]);
                ++times2;
                if (state1 == state2) break;
            }
        }
    }

    cout << (times1 + times2) % 99999997 << endl;

    return 0;
}