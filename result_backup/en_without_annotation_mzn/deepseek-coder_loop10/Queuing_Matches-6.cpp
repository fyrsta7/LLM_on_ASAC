#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <limits>

using namespace std;

int n;
vector<int> a, b;

int factorial(int f) {
    return f == 0 ? 1 : factorial(f - 1) * f;
}

int calculate_min_distance() {
    int len = factorial(n);
    vector<vector<int>> permutations(len, vector<int>(n));
    vector<int> perm(n);
    for (int i = 0; i < n; ++i) perm[i] = i + 1;

    int idx = 0;
    do {
        permutations[idx++] = perm;
    } while (next_permutation(perm.begin(), perm.end()));

    int min_distance = numeric_limits<int>::max();
    for (int i = 0; i < len; ++i) {
        int distance = 0;
        for (int j = 0; j < n; ++j) {
            distance += pow(a[j] - permutations[i][j], 2);
        }
        min_distance = min(min_distance, distance);
    }
    return min_distance;
}

int main() {
    cin >> n;
    a.resize(n);
    b.resize(n);
    for (int i = 0; i < n; ++i) cin >> a[i];
    for (int i = 0; i < n; ++i) cin >> b[i];

    int min_distance = calculate_min_distance();

    vector<vector<int>> state1(n * n + 1, vector<int>(n));
    vector<vector<int>> state2(n * n + 1, vector<int>(n));
    vector<int> exchange1(n * n + 1), exchange2(n * n + 1);

    state1[0] = a;
    state2[0] = b;

    int times1 = 0, times2 = 0;

    while (true) {
        int current_distance = 0;
        for (int i = 0; i < n; ++i) {
            current_distance += pow(state1[times1][i] - state2[times2][i], 2);
        }
        if (current_distance == min_distance) break;

        if (times1 < n * n) {
            int loc = rand() % (n - 1) + 1;
            state1[times1 + 1] = state1[times1];
            swap(state1[times1 + 1][loc], state1[times1 + 1][loc + 1]);
            exchange1[times1 + 1] = loc;
            times1++;
        }

        if (times2 < n * n) {
            int loc = rand() % (n - 1) + 1;
            state2[times2 + 1] = state2[times2];
            swap(state2[times2 + 1][loc], state2[times2 + 1][loc + 1]);
            exchange2[times2 + 1] = loc;
            times2++;
        }
    }

    cout << (times1 + times2) % 99999997 << endl;

    return 0;
}
