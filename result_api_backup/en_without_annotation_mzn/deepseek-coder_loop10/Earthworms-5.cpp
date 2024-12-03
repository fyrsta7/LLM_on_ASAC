#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    int N, M, Q, u, v, t;
    cin >> N >> M >> Q >> u >> v >> t;
    vector<int> A(N);
    for (int i = 0; i < N; ++i) cin >> A[i];

    vector<vector<int>> S(M + 1, vector<int>(N + M + 1, 0));
    for (int i = 1; i <= N; ++i) S[0][i] = A[i - 1];

    vector<int> pos(M);
    for (int m = 0; m < M; ++m) {
        int max_val = *max_element(S[m].begin() + 1, S[m].begin() + N + m + 1);
        int val0 = max_val * u / v;
        int val1 = max_val - val0;
        for (int i = 1; i <= N + m; ++i) {
            if (S[m][i] == max_val) {
                pos[m] = i;
                break;
            }
        }
        S[m + 1][pos[m]] = val0;
        S[m + 1][N + m + 1] = val1;
        for (int i = 1; i <= N + m; ++i) {
            if (i != pos[m]) {
                S[m + 1][i] = S[m][i] + Q;
            }
        }
    }

    vector<int> ans1(M / t);
    for (int i = 0; i < M / t; ++i) {
        ans1[i] = S[i * t][pos[i * t]];
    }

    vector<int> index_S(N + M);
    for (int i = 0; i < N + M; ++i) index_S[i] = i + 1;
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
