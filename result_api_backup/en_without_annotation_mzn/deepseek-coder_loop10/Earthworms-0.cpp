#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    int N, M, Q, u, v, t;
    cin >> N >> M >> Q >> u >> v >> t;
    vector<int> A(N);
    for (int i = 0; i < N; ++i) {
        cin >> A[i];
    }

    vector<vector<int>> S(M + 1, vector<int>(N + M));
    vector<int> pos(M);

    for (int i = 0; i < N; ++i) {
        S[0][i] = A[i];
    }

    for (int m = 0; m < M; ++m) {
        int val = *max_element(S[m].begin(), S[m].begin() + N + m);
        int val0 = val * u / v;
        int val1 = val - val0;
        int max_pos = max_element(S[m].begin(), S[m].begin() + N + m) - S[m].begin();
        pos[m] = max_pos;

        for (int i = 0; i < N + m; ++i) {
            if (i == max_pos) {
                S[m + 1][i] = val0;
            } else {
                S[m + 1][i] = S[m][i] + Q;
            }
        }
        S[m + 1][N + m] = val1;
    }

    vector<int> ans1(M / t);
    for (int i = 0; i < M / t; ++i) {
        ans1[i] = S[i * t][pos[i * t]];
    }

    vector<int> index_S(N + M);
    for (int i = 0; i < N + M; ++i) {
        index_S[i] = i;
    }
    sort(index_S.begin(), index_S.end(), [&](int a, int b) {
        return S[M][a] < S[M][b];
    });

    for (int i = 0; i < M / t; ++i) {
        cout << ans1[i] << " ";
    }
    cout << endl;

    for (int i = 0; i < N + M; ++i) {
        cout << S[M][index_S[i]] << " ";
    }
    cout << endl;

    return 0;
}
