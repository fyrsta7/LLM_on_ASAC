#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    int N;
    cin >> N;
    vector<vector<int>> bond(N, vector<int>(N));
    for (int i = 0; i < N; ++i) {
        for (int j = i + 1; j < N; ++j) {
            cin >> bond[i][j];
            bond[j][i] = bond[i][j];
        }
    }

    vector<int> freeGenerals(N);
    for (int i = 0; i < N; ++i) {
        freeGenerals[i] = i;
    }

    int maxBondingLevel = 0;
    for (int i = 0; i < N; ++i) {
        for (int j = i + 1; j < N; ++j) {
            maxBondingLevel = max(maxBondingLevel, bond[i][j]);
        }
    }

    cout << 1 << endl;
    cout << maxBondingLevel << endl;

    return 0;
}
