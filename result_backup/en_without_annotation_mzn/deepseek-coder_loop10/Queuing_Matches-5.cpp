#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

int n;
vector<int> a, b;

int factorial(int f) {
    return f == 0 ? 1 : factorial(f - 1) * f;
}

int calculateMinDistance(const vector<int>& perm) {
    int distance = 0;
    for (int i = 0; i < n; ++i) {
        distance += pow(a[i] - perm[i], 2);
    }
    return distance;
}

int main() {
    cin >> n;
    a.resize(n);
    b.resize(n);
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
    for (const auto& perm : permutations) {
        min_distance = min(min_distance, calculateMinDistance(perm));
    }

    int times1 = 0, times2 = 0;
    vector<int> state1 = a, state2 = b;

    while (calculateMinDistance(state1) != min_distance) {
        for (int i = 0; i < n - 1; ++i) {
            swap(state1[i], state1[i + 1]);
            times1++;
            if (calculateMinDistance(state1) == min_distance) break;
            swap(state1[i], state1[i + 1]);
            times1--;
        }
    }

    while (calculateMinDistance(state2) != min_distance) {
        for (int i = 0; i < n - 1; ++i) {
            swap(state2[i], state2[i + 1]);
            times2++;
            if (calculateMinDistance(state2) == min_distance) break;
            swap(state2[i], state2[i + 1]);
            times2--;
        }
    }

    cout << (times1 + times2) % 99999997 << endl;

    return 0;
}
