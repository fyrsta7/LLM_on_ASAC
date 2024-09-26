#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const int MAXN = 100000;
const int MAXM = 7000000;
const int MAXQ = 200;
int N, M, Q, u, v, t;
vector<int> A(MAXN);
vector<vector<int>> S(MAXM + 1, vector<int>(MAXN + MAXM + 1, 0));
vector<int> pos(MAXM);
vector<int> ans1(MAXM / MAXQ);
vector<int> ans2((MAXN + MAXM) / MAXQ);
vector<int> index_S(MAXN + MAXM);

// Function to check constraint
bool ok(int m) {
    int val = *max_element(S[m].begin() + 1, S[m].begin() + 1 + N + m);
    int val0 = val * u / v;
    int val1 = val - val0;
    if (S[m][pos[m]] != val) return false;
    S[m + 1][pos[m]] = val0;
    S[m + 1][N + m + 1] = val1;
    for (int i = 1; i <= N + m; ++i) {
        if (i != pos[m]) {
            if (S[m + 1][i] != S[m][i] + Q) return false;
        }
    }
    return true;
}

int main() {
    // Input reading
    cin >> N >> M >> Q >> u >> v >> t;
    for (int i = 1; i <= N; ++i) cin >> A[i];
    for (int i = 1; i <= N; ++i) S[0][i] = A[i];

    // Constraint checking
    for(int m = 0; m < M-1; ++m) {
        if (!ok(m)) {
            cout << "Constraints not satisfied\n";
            return 1;
        }
    }

    for(int i = 1; i <= M/t; ++i) {
        ans1[i] = S[(i * t) - 1][pos[i * t - 1]];
    }
    
    iota(index_S.begin(), index_S.end(), 1);
    sort(index_S.begin(), index_S.end(), [&](int a, int b) { return S[M][a] < S[M][b]; });

    // Output the result
    for (int i = 1; i <= M / t; ++i) {
        cout << ans1[i] << " ";
    }
    cout << endl;
    for (int i = 1; i <= M + N; ++i) {
        cout << S[M][index_S[i]] << " ";
    }
    cout << endl;

    return 0;
}