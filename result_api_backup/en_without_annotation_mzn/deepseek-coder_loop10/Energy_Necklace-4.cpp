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

    int ans = 0;
    for (int i = 0; i < N - 1; ++i) {
        int j = choose[i];
        int len = N - i;
        int prev = (j > 1) ? j - 1 : len;
        int next = (j < len) ? j + 1 : 1;
        ans += steps[i][j] * steps[i][prev] * steps[i][next];

        for (int k = 1; k < choose[i]; ++k) {
            steps[i + 1][k] = steps[i][k];
        }
        for (int k = choose[i] + 1; k <= len; ++k) {
            steps[i + 1][k - 1] = steps[i][k];
        }
    }

    cout << ans << endl;
    return 0;
}
