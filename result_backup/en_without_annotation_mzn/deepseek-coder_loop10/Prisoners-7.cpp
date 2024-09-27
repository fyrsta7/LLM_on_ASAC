#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>

using namespace std;

int N, M;
vector<vector<int>> conflict;

int calculateValue(const vector<int>& prison) {
    if (prison.size() < 2) return 0;
    int maxConflict = 0;
    for (int i = 0; i < M; ++i) {
        if (binary_search(prison.begin(), prison.end(), conflict[i][0]) &&
            binary_search(prison.begin(), prison.end(), conflict[i][1])) {
            maxConflict = max(maxConflict, conflict[i][2]);
        }
    }
    return maxConflict;
}

int main() {
    cin >> N >> M;
    conflict.resize(M, vector<int>(3));
    for (int i = 0; i < M; ++i) {
        cin >> conflict[i][0] >> conflict[i][1] >> conflict[i][2];
    }

    int minFinalValue = INT_MAX;

    for (int mask = 0; mask < (1 << N); ++mask) {
        vector<int> prison1, prison2;
        for (int i = 0; i < N; ++i) {
            if (mask & (1 << i)) {
                prison1.push_back(i + 1);
            } else {
                prison2.push_back(i + 1);
            }
        }

        int value1 = calculateValue(prison1);
        int value2 = calculateValue(prison2);
        int finalValue = max(value1, value2);
        minFinalValue = min(minFinalValue, finalValue);
    }

    cout << minFinalValue << endl;
    return 0;
}
