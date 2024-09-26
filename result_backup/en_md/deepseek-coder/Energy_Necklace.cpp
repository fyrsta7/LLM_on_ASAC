#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

const int MAXN = 105;
int N, beads[MAXN], dp[MAXN][MAXN];

int main() {
    cin >> N;
    for (int i = 0; i < N; ++i) {
        cin >> beads[i];
    }

    for (int len = 2; len < N; ++len) {
        for (int i = 0; i < N; ++i) {
            int j = (i + len) % N;
            dp[i][j] = 0;
            for (int k = (i + 1) % N; k != j; k = (k + 1) % N) {
                int energy = beads[i] * beads[k] * beads[j];
                dp[i][j] = max(dp[i][j], dp[i][k] + dp[k][j] + energy);
            }
        }
    }

    int maxEnergy = 0;
    for (int i = 0; i < N; ++i) {
        maxEnergy = max(maxEnergy, dp[i][(i + N - 1) % N]);
    }

    cout << maxEnergy << endl;
    return 0;
}
