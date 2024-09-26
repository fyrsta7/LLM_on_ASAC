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

    int ans = 0;
    for (int i = 1; i < N; ++i) {
        for (int j = 0; j < N - i; ++j) {
            steps[i][j] = steps[i-1][j];
        }
        int max_product = 0;
        for (int j = 0; j < N - i; ++j) {
            int prev = (j > 0) ? j - 1 : N - i - 1;
            int next = (j < N - i - 1) ? j + 1 : 0;
            int product = steps[i][j] * steps[i][prev] * steps[i][next];
            if (product > max_product) {
                max_product = product;
            }
        }
        ans += max_product;
    }

    cout << ans << endl;
    return 0;
}
