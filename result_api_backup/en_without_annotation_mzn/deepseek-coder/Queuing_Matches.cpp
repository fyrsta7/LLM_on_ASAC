#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
using namespace std;

int factorial(int f) {
    return f == 0 ? 1 : factorial(f - 1) * f;
}

int main() {
    int n;
    cin >> n;
    vector<int> a(n), b(n);
    for (int i = 0; i < n; ++i) cin >> a[i];
    for (int i = 0; i < n; ++i) cin >> b[i];

    int len = factorial(n);
    vector<vector<int>> permutations(len, vector<int>(n));
    vector<int> perm(n);
    for (int i = 0; i < n; ++i) perm[i] = i + 1;

    int idx = 0;
    do {
        permutations[idx++] = perm;
    } while (next_permutation(perm.begin(), perm.end()));

    int min_distance = INT_MAX;
    for (int i = 0; i < len; ++i) {
        int distance = 0;
        for (int j = 0; j < n; ++j) {
            distance += pow(a[j] - permutations[i][j], 2);
        }
        min_distance = min(min_distance, distance);
    }

    int times1 = 0, times2 = 0;
    vector<vector<int>> state1(1, a), state2(1, b);
    while (true) {
        int distance1 = 0, distance2 = 0;
        for (int i = 0; i < n; ++i) {
            distance1 += pow(state1[times1][i] - state2[times2][i], 2);
            distance2 += pow(state1[times1][i] - state2[times2][i], 2);
        }
        if (distance1 == min_distance || distance2 == min_distance) break;

        if (times1 <= times2) {
            vector<int> new_state(state1[times1]);
            swap(new_state[times1 % (n - 1)], new_state[times1 % (n - 1) + 1]);
            state1.push_back(new_state);
            ++times1;
        } else {
            vector<int> new_state(state2[times2]);
            swap(new_state[times2 % (n - 1)], new_state[times2 % (n - 1) + 1]);
            state2.push_back(new_state);
            ++times2;
        }
    }

    cout << (times1 + times2) % 99999997 << endl;
    return 0;
}