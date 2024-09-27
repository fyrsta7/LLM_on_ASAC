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

    vector<int> perm(n);
    for (int i = 0; i < n; ++i) perm[i] = i;

    do {
        int distance = 0;
        for (int i = 0; i < n; ++i) {
            distance += pow(a[i] - b[perm[i]], 2);
        }
        min_distance = min(min_distance, distance);
    } while (next_permutation(perm.begin(), perm.end()));

    int times1 = 0, times2 = 0;
    vector<int> state1 = a, state2 = b;

    while (true) {
        int distance = 0;
        for (int i = 0; i < n; ++i) {
            distance += pow(state1[i] - state2[i], 2);
        }
        if (distance == min_distance) break;

        bool swapped1 = false, swapped2 = false;
        for (int i = 0; i < n - 1; ++i) {
            swap(state1[i], state1[i + 1]);
            int new_distance = 0;
            for (int j = 0; j < n; ++j) {
                new_distance += pow(state1[j] - state2[j], 2);
            }
            if (new_distance < distance) {
                swapped1 = true;
                times1++;
                break;
            }
            swap(state1[i], state1[i + 1]);

            swap(state2[i], state2[i + 1]);
            new_distance = 0;
            for (int j = 0; j < n; ++j) {
                new_distance += pow(state1[j] - state2[j], 2);
            }
            if (new_distance < distance) {
                swapped2 = true;
                times2++;
                break;
            }
            swap(state2[i], state2[i + 1]);
        }

        if (!swapped1 && !swapped2) break;
    }

    cout << (times1 + times2) % 99999997 << endl;
    return 0;
}