#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    int N;
    cin >> N;
    vector<int> beads(N);
    for (int i = 0; i < N; ++i) {
        cin >> beads[i];
    }

    vector<vector<int>> steps(N, vector<int>(N));
    for (int i = 0; i < N; ++i) {
        steps[0][i] = beads[i];
    }

    vector<int> choose(N);
    for (int i = 1; i < N; ++i) {
        choose[i] = N - i + 1;
    }

    for (int i = 1; i < N; ++i) {
        for (int j = 0; j < choose[i] - 1; ++j) {
            steps[i][j] = steps[i - 1][j];
        }
        for (int j = choose[i]; j < N - i + 1; ++j) {
            steps[i][j - 1] = steps[i - 1][j];
        }
    }

    int ans = 0;
    for (int i = 0; i < N - 1; ++i) {
        int j = choose[i] - 1;
        int len = N - i;
        int prev = (j > 0) ? j - 1 : len - 1;
        int next = (j < len - 1) ? j + 1 : 0;
        ans += steps[i][j] * steps[i][prev] * steps[i][next];
    }

    cout << ans << endl;
    return 0;
}
