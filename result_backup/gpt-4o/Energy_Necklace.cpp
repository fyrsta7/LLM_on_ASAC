#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int maxEnergy(vector<int> &marks, int N) {
    vector<vector<int>> dp(2 * N, vector<int>(2 * N, 0));

    for (int len = 2; len <= N; ++len) {
        for (int i = 0; i < 2 * N - len; ++i) {
            int j = i + len;
            for (int k = i + 1; k < j; ++k) {
                int energy = marks[i] * marks[k] * marks[j];
                dp[i][j] = max(dp[i][j], dp[i][k] + dp[k][j] + energy);
            }
        }
    }

    int max_energy = 0;
    for (int i = 0; i < N; ++i) {
        max_energy = max(max_energy, dp[i][i + N]);
    }
    return max_energy;
}

int main() {
    int N;
    cin >> N;

    vector<int> marks(N);
    for (int i = 0; i < N; ++i) {
        cin >> marks[i];
    }

    marks.insert(marks.end(), marks.begin(), marks.end());
    cout << maxEnergy(marks, N) << endl;

    return 0;
}