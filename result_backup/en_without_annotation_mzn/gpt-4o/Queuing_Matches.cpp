#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <climits>

using namespace std;

int factorial(int f) {
    if (f == 0)
        return 1;
    return factorial(f - 1) * f;
}

int main() {
    int n;
    cin >> n;
    vector<int> a(n), b(n);
    for (int i = 0; i < n; i++)
        cin >> a[i];
    for (int i = 0; i < n; i++)
        cin >> b[i];

    vector<vector<int>> permutations;
    vector<int> perm(n);
    for (int i = 0; i < n; i++)
        perm[i] = i + 1;
    do {
        permutations.push_back(perm);
    } while (next_permutation(perm.begin(), perm.end()));

    int len = factorial(n);

    int min_distance = INT_MAX;
    for (int i = 0; i < len; i++) {
        int distance = 0;
        for (int j = 0; j < n; j++) {
            distance += pow(a[j] - permutations[i][j], 2);
        }
        if (distance < min_distance) {
            min_distance = distance;
        }
    }

    int max_exchange = n * n;
    vector<vector<int>> state1(max_exchange + 1, vector<int>(n));
    vector<vector<int>> state2(max_exchange + 1, vector<int>(n));
    vector<int> exchange1(max_exchange + 1);
    vector<int> exchange2(max_exchange + 1);

    for (int i = 0; i < n; i++) {
        state1[0][i] = a[i];
        state2[0][i] = b[i];
    }

    auto exchange = [&](vector<int> &before, vector<int> &after, int loc) {
        for (int i = 0; i < loc - 1; i++)
            after[i] = before[i];
        for (int i = loc + 2 - 1; i < n; i++)
            after[i] = before[i];
        after[loc - 1] = before[loc];
        after[loc] = before[loc - 1];
    };

    int times1 = 0, times2 = 0;

    for (int i = 1; i <= max_exchange; i++) {
        if (times1 < i) {
            exchange(state1[i - 1], state1[i], exchange1[i - 1]);
            times1++;
        }
        if (times2 < i) {
            exchange(state2[i - 1], state2[i], exchange2[i - 1]);
            times2++;
        }
        int distance = 0;
        for (int j = 0; j < n; j++) {
            distance += pow(state1[times1][j] - state2[times2][j], 2);
        }
        if (distance == min_distance) break;
    }

    cout << (times1 + times2) % 99999997;
    return 0;
}