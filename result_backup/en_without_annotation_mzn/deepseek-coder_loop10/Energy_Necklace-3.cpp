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
    vector<int> choose(N);

    for (int i = 0; i < N; ++i) {
        steps[0][i] = beads[i];
    }

    for (int i = 1; i < N; ++i) {
        for (int j = 0; j < N - i; ++j) {
            steps[i][j] = steps[i-1][j];
        }
        int max_val = -1;
        int max_idx = -1;
        for (int j = 0; j < N - i; ++j) {
            int val = steps[i-1][j] * steps[i-1][(j+1)%(N-i+1)] * steps[i-1][(j-1+N-i+1)%(N-i+1)];
            if (val > max_val) {
                max_val = val;
                max_idx = j;
            }
        }
        choose[i-1] = max_idx;
        for (int j = max_idx; j < N - i - 1; ++j) {
            steps[i][j] = steps[i-1][j+1];
        }
    }

    int ans = 0;
    for (int i = 0; i < N - 1; ++i) {
        ans += steps[i][choose[i]] * steps[i][(choose[i]+1)%(N-i)] * steps[i][(choose[i]-1+N-i)%(N-i)];
    }

    cout << ans << endl;
    return 0;
}
