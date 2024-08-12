#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

bool isPossible(const vector<int>& rocks, int M, int mid) {
    int removed = 0;
    int prev = 0;
    for (int rock : rocks) {
        if (rock - prev < mid) {
            removed++;
        } else {
            prev = rock;
        }
    }
    return removed <= M;
}

int main() {
    int L, N, M;
    cin >> L >> N >> M;
    vector<int> rocks(N + 2);
    rocks[0] = 0;
    for (int i = 1; i <= N; ++i) {
        cin >> rocks[i];
    }
    rocks[N + 1] = L;

    int left = 1, right = L;
    while (left < right) {
        int mid = left + (right - left + 1) / 2;
        if (isPossible(rocks, M, mid)) {
            left = mid;
        } else {
            right = mid - 1;
        }
    }
    cout << left << endl;
    return 0;
}
