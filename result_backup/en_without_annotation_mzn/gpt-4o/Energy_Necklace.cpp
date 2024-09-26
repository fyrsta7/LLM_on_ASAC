#include <iostream>
#include <vector>
using namespace std;

int precede(int j, int len) {
    return (j > 1) ? j - 1 : len;
}

int follow(int j, int len) {
    return (j < len) ? j + 1 : 1;
}

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

    vector<int> choose(N, 1);
    for (int i = 1; i < N; ++i) {
        choose[i] = min(N - i + 1, 1);
    }

    for (int i = 1; i < N; ++i) {
        for (int j = 0; j < choose[i-1] - 1; ++j) {
            steps[i][j] = steps[i-1][j];
        }
        for (int j = choose[i-1]; j < N - i + 1; ++j) {
            steps[i][j - 1] = steps[i-1][j];
        }
    }

    int ans = 0;
    for (int i = 0; i < N - 1; ++i) {
        ans += steps[i][choose[i]] * steps[i][precede(choose[i], N - i + 1)] * steps[i][follow(choose[i], N - i + 1)];
    }

    cout << ans << endl;
    return 0;
}